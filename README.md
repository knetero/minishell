# Minishell - Custom UNIX Shell Implementation

A lightweight UNIX shell implementation in C supporting core shell functionalities and process management.

[![C](https://img.shields.io/badge/C-99-blue)](https://www.gnu.org/software/gnu-c-manual/)

## Features

- **Command interpretation** with basic syntax:
  - Pipes (`|`)
  - Redirections (`>`, `>>`, `<`)
  - Environment variables (`$VAR`)
- **Process management**:
  - Fork/exec workflow
  - Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)
  - Exit status codes
- **Built-in commands**:
  - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Error handling**:
  - Syntax error detection
  - Command not found handling
  - Permission validation
