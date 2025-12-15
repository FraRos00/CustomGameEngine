{
  description = "Dev environment for CustomEngine";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
      in {
        devShells.default = pkgs.mkShell {
          name = "customengine-env";

          buildInputs = [
            pkgs.cmake
            pkgs.gcc
            pkgs.raylib
            pkgs.glfw
            pkgs.pkg-config
            pkgs.gdb
            pkgs.clang-tools      # clangd, clang-format, clang-tidy
          ];

          shellHook = ''
            echo "🔧 DevShell attiva per CustomEngine!"
          '';
        };
      }
    );
}
