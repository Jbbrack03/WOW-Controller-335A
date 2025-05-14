# Injection Validation Test

## Steps
1. Build `controller_dll.dll` and inject into a running Wow.exe process.
2. Confirm that `C:/temp/controller_log.txt` is created and logs controller status every second.
3. Remove the DLL and confirm polling stops.

## Acceptance Criteria
- Log file confirms successful injection and controller polling.
