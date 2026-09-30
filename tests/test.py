#!/usr/bin/env python3

import glob
import os
import shutil
import subprocess

GREEN = "\033[32m"
RED = "\033[31m"
RESET = "\033[0m"

tests = glob.glob("tests/*") + glob.glob("tests/*/*")

passed = 0
failed = 0

print("Running tests...\n")

for test in tests:
    if os.path.isdir(test):
        continue

    if os.path.abspath(test) == os.path.abspath(__file__):
        continue

    if test.endswith(".py"):
        command = ["python3", test]
    elif test.endswith(".sh"):
        command = ["sh", test]
    else:
        continue

    result = subprocess.run(
        command,
        capture_output=True,
        text=True,
    )

    name = os.path.basename(test)

    if result.returncode == 0:
        print(f"{GREEN}PASS{RESET} {name}")
        passed += 1
    else:
        print(f"{RED}FAIL{RESET} {name}")
        failed += 1

        if result.stdout:
            print(result.stdout)

        if result.stderr:
            print(result.stderr)

    # Clean generated test artifacts.
    for path in glob.glob("tests/*/bin"):
        if os.path.isdir(path):
            shutil.rmtree(path)

print()
print(f"{passed} passed, {failed} failed")

if failed:
    exit(1)

print(f"{GREEN}All tests passed{RESET}")