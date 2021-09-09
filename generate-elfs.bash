#!/usr/bin/env bash
nix-build . -A user-1 -o result-user1
nix-build . -A user-2 -o result-user2
nix-build . -A runner-0 -o result
