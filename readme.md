[Source](https://stackoverflow.com/questions/13534167/execute-command-just-before-mac-going-to-sleep)

get mac address:
system_profiler SPBluetoothDataType | awk '/Connected:/,/Not Connected:/ {print}' | sed -e 's/^[ \t]*//' | awk '/Address:/ {print $2}

launchctl load ~/Library/LaunchAgents/com.user.disableSony.plist
