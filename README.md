# XCPP

demo for cross-platform C++ project

To add includePath, add an item in `.vscode/c_cpp_properities.json` objects:

```
"compileCommands": "${workspaceFolder}/.vscode/compile_commands.json"
```

Rebuild with 
```
xmake project -k compile_commands 
```

