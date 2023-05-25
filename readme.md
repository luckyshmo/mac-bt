[Source](https://stackoverflow.com/questions/13534167/execute-command-just-before-mac-going-to-sleep)

Get mac addresses of BT devices if needed:
```
system_profiler SPBluetoothDataType | awk '/Connected:/,/Not Connected:/ {print}' | sed -e 's/^[ \t]*//' | awk '/Address:/ {print $2}
```

Switch on daemon. 
```
launchctl load ~/Library/LaunchAgents/com.user.disableSony.plist
```

Switch off daemon. 
```
launchctl unload ~/Library/LaunchAgents/com.user.disableSony.plist
```

Instruction:
1) change path and command in beforesleep.c
2) build bin: task build
3) change path in com.user.disableSony.plist
4) copy com.user.disableSony.plist to ~/Library/LaunchAgents/
5) run daemon