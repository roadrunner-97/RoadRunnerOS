{
  description = "i686 OS development environment";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs {
        inherit system;
      };

      cross = pkgs.pkgsCross.i686-embedded;
    in {
      devShells.${system}.default = pkgs.mkShell {
        packages = [
          # Native build tools
          pkgs.cmake
          pkgs.ninja
          pkgs.ccache
          pkgs.gnumake
          pkgs.git

          # i686-elf cross toolchain
          cross.stdenv.cc
          cross.binutils

          # Very useful for OS dev
          pkgs.gdb
          pkgs.qemu
          pkgs.xorriso
          pkgs.grub2
          pkgs.mtools
          pkgs.bochs
        ];

        shellHook = ''
          export CC=i686-elf-gcc
          export CXX=i686-elf-g++
          export AR=i686-elf-ar
          export AS=i686-elf-as
          export LD=i686-elf-ld
          export OBJCOPY=i686-elf-objcopy
          export OBJDUMP=i686-elf-objdump

          export CCACHE_DIR="$PWD/.ccache"

          echo "i686 OS development environment"
          echo "CC: $(command -v $CC)"
        '';
      };
    };
}