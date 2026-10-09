# ShellForge – System Design

## 1. Project Overview

ShellForge is a Unix-like shell implemented in C as an Operating Systems and Systems Programming project.

It demonstrates process creation, IPC, signals, file redirection, POSIX threads, synchronization, deadlock handling and job control.

## 2. Architecture

```text
Input
  |
  v
Parser
  |
  v
Built-in / External Command
  |
  +---- Process Management
  |
  +---- Pipes
  |
  +---- Redirection
  |
  +---- Signals
  |
  +---- Threads
  |
  +---- Job Control
