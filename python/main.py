#!/usr/bin/env python3
import os
import re
import subprocess
import textwrap

REPO_URL = "https://github.com/robsoncouto/arduino-songs.git"
REPO_DIR = "arduino-songs"
OUTPUT_DIR = "generated_headers"

# Regex helpers
TEMPO_RE = re.compile(r'\bint\s+tempo\s*=\s*([0-9]+)\s*;')
MELODY_START_RE = re.compile(r'\bint\s+melody\s*\[\s*\]\s*=\s*\{')
MELODY_END_RE = re.compile(r'\};\s*$')

def ensure_repo():
    if not os.path.isdir(REPO_DIR):
        print(f"Cloning {REPO_URL} into {REPO_DIR} ...")
        subprocess.check_call(["git", "clone", REPO_URL, REPO_DIR])
    else:
        print(f"Using existing repo at {REPO_DIR}")

def sanitize_song_name(path):
    """
    Use the folder name as song identifier, e.g. cannonind/cannonind.ino -> cannonind.
    """
    folder = os.path.basename(os.path.dirname(path))
    # Make it a valid C identifier
    identifier = re.sub(r'\W+', '_', folder)
    return identifier

def extract_from_ino(path):
    with open(path, encoding="utf-8") as f:
        lines = f.readlines()

    # 1) Extract tempo (first match)
    tempo_value = None
    for line in lines:
        m = TEMPO_RE.search(line)
        if m:
            tempo_value = m.group(1)
            break

    # 2) Extract melody array (from "int melody[] = {" to the matching "};")
    melody_lines = []
    inside_melody = False
    for line in lines:
        if not inside_melody:
            if MELODY_START_RE.search(line):
                inside_melody = True
                melody_lines.append(line)
        else:
            melody_lines.append(line)
            if MELODY_END_RE.search(line):
                break

    melody_block = "".join(melody_lines)

    return {
        "tempo": tempo_value,
        "melody_block": melody_block,
    }

def build_header_content(song_name, data):
    # Reconstruct tempo / melody / derived vars
    # Keep original melody formatting as much as possible
    header = textwrap.dedent(f"""\
        // Auto-generated from robsoncouto/arduino-songs
        // Song: {song_name}
        #include <Notes.h>
        #pragma once
        // tempo for this song
        int tempo = {data["tempo"]};

        // melody for this song
        {data["melody_block"].strip()}

        // number of notes
        int notes = sizeof(melody) / sizeof(melody[0]) / 2;

        // whole note duration in ms
        int wholenote = (60000 * 4) / tempo;

        // durations array - to be computed from melody at runtime
        int durations[sizeof(melody) / sizeof(melody[0]) / 2];
    """)
    return header

def process_repo():
    if not os.path.isdir(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR, exist_ok=True)

    for root, dirs, files in os.walk(REPO_DIR):
        for fname in files:
            if not fname.endswith(".ino"):
                continue
            ino_path = os.path.join(root, fname)
            song_name = sanitize_song_name(ino_path)
            print(f"Processing {ino_path} -> {song_name}.h")

            data = extract_from_ino(ino_path)
            if not data:
                continue

            header_content = build_header_content(song_name, data)
            out_path = os.path.join(OUTPUT_DIR, f"{song_name}.h")
            with open(out_path, "w", encoding="utf-8") as f:
                f.write(header_content)

def main():
    ensure_repo()
    process_repo()
    print(f"Done. Headers are in '{OUTPUT_DIR}'.")

if __name__ == "__main__":
    main()
