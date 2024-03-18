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
<br>
  That's all.
<br>
There’s no need to fuss over such matters, let's get started. Let's go!


### Build (Old)
- install [MinGW](https://sourceforge.net/projects/mingw/)
- git clone https://github.com/Chanomhub/Check.git
- cd scr\RPGMAKERMV\{Choose}
- gcc main.c
### Build (New)
- install [Clang](https://github.com/llvm/llvm-project)
- git clone https://github.com/Chanomhub/Check.git
- cd scr\RPGMAKERMV\{Choose}
- clang main.c

# GCC
![Screenshot 2024-03-18 074718](https://github.com/Chanomhub/Check/assets/121768693/1b07502e-5fd6-4240-ad35-f18581f1877a)
# Clang
![Screenshot 2024-03-18 074707](https://github.com/Chanomhub/Check/assets/121768693/dd2b9935-2f7f-4c99-9d7a-948337db80ef)

The test results are not very accurate because when I built with "Clang" I modified the code to prevent buffer overflow, but in "GCC" I used old code.




