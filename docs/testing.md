# ShellForge Testing

## Basic Commands

| Test | Command | Result |
|---|---|---|
| T01 | pwd | Pass |
| T02 | ls | Pass |
| T03 | cd | Pass |
| T04 | exit | Pass |

## Pipes

| Test | Command | Result |
|---|---|---|
| T05 | ls \| grep txt | Pass |

## Redirection

| Test | Command | Result |
|---|---|---|
| T06 | ls > out.txt | Pass |
| T07 | cat < out.txt | Pass |
| T08 | ls >> out.txt | Pass |

## Signals

| Test | Action | Result |
|---|---|---|
| T09 | Ctrl+C | Pass |
| T10 | Ctrl+Z | Pass |

## Concurrency

| Test | Result |
|---|---|
| T11 | POSIX thread | Pass |
| T12 | Mutex | Pass |
| T13 | Race condition | Pass |
| T14 | Deadlock | Pass |
| T15 | Deadlock prevention | Pass |

## Job Control

| Test | Result |
|---|---|
| T16 | command & | Pass |
| T17 | jobs | Pass |
| T18 | bg %1 | Pass |
| T19 | fg %1 | Pass |
| T20 | Multiple jobs | Pass |
