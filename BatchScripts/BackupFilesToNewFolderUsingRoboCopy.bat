robocopy "C:\V DRIVE" "X:\DailyFullBackup" /s /e /xd "bin" "obj" ".cov" /xf "*.ico" /r:5 /xo /log:"X:\ClientsCopyLog.txt" /np /eta
