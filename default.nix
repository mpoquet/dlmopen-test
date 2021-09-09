{ pkgs ? import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/21.05.tar.gz") {}
}:

let
  gendrv = v: name: dir: inputs: pkgs.stdenv.mkDerivation rec {
    pname = name;
    version = v;

    buildInputs = [pkgs.meson pkgs.ninja pkgs.pkgconfig] ++ inputs;
    src = pkgs.lib.sourceByRegex dir [
      "^.*\.c"
      "^meson\.build"
      "^meson_options\.txt"
    ];
    mesonFlags = ["-Dversion=${v}"];
  };
  self = rec {
    base-0 = gendrv "0" "base" ./base [];
    base-1 = gendrv "1" "base" ./base [];
    base-2 = gendrv "2" "base" ./base [];
    user-1 = gendrv "1" "user" ./user [base-1];
    user-2 = gendrv "2" "user" ./user [base-2];
    runner-0 = gendrv "0" "runner" ./runner [base-0];
  };
in
  self
