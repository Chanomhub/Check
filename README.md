### What is this?
- This is an add-on for checking the correctness of file locations. <br>
  And distinguish which engine the game uses to develop.
- This add-on was developed by CrypticDay using C language.
- It might not be very useful if you use this add-on for non-H games.

### Necessary conditions
-   ̷G̷C̷C̷
-   [Clang](https://github.com/llvm/llvm-project)
-   [Git](https://git-scm.com/)
-   (Use visual studio?) No! you don't need to because I use [Vim](https://www.vim.org/).


(Why don't I just use GCC?)
<br>
Because it's cooler! I'm joking because "Clang LLVM" is a new and stable compiler that can take your programs to the next level.
<br>
If you don't want to waste time debugging your code.


### Build (Old)
- install [MinGW](https://www.mingw-w64.org/)
- git clone https://github.com/Chanomhub/Check.git
- cd Check/scr/RPGMAKERMV (Linux)
- cd Check\scr\RPGMAKERMV (Windows)
- gcc main.c
### Build (New)
- install [Clang](https://github.com/llvm/llvm-project)
- git clone https://github.com/Chanomhub/Check.git
- cd Check/scr/RPGMAKERMV (Linux)
- cd Check\scr\RPGMAKERMV (Windows)
- clang main.c


### Mode
"Automatic" this will be the default. <br>
"Advanced" You must run it manually in cases where it can be determined that the game uses a game development engine.

|     Type      |   Automatic   |   Advanced    |
| :---: | :---: | :---: |
| RPGM  | ✔️  | ❌
| Unity  | ❌  | ❌
|  RPG Wolf  | ❌  | ❌
| Godot Engine  | ❌  | ❌
| Ren’Py  | ❌  | ❌
| Unreal Engine  | ❌  | ❌
| Adobe Flash Player  | ❌  | ❌
| Game Maker Studio 2  | ❌  | ❌
| Pixel Game Maker MV player  | ❌  | ❌

