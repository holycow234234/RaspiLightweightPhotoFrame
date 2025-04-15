/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute 'raylib_compile_execute' script
*   Note that compiled executable is placed in the same folder as .c file
*
*   To test the examples on Web, press F6 and execute 'raylib_compile_execute_web' script
*   Web version of the program is generated in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(int argc, char *argv[]){
    
    if(argc != 3/*4*/){//todo update when adding variable for media dir
        printf("ERROR | wrong number of arguments\n");
        printf("Usage: <width> <height>\n");
        return -1;
    }
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth;
    const int screenHeight;

    sscanf(argv[1],"%d", &screenWidth);
    sscanf(argv[2],"%d", &screenHeight);

    printf("creating screen with height %d width %d\n",screenWidth,screenHeight);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    Texture2D texture = LoadTexture("trees.jpg"); 
    //--------------------------------------------------------------------------------------
    bool show = true;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();


        //printf("width %d height%d\n",texture.height,texture.width);
        float scale = 1.0;
        Vector2 position = (Vector2){0,0}; //todo
        if(texture.width > screenWidth || texture.height > screenHeight){
            //printf("check one\n");
            if(texture.width > texture.height){
                scale = (float)screenWidth/(float)texture.width;
            }else{
                scale = (float)screenHeight/(float)texture.height;
            }
        }else if(texture.width < screenWidth || texture.height < screenHeight){
            //printf("check two\n");
            if(screenWidth > screenHeight){
                scale = (float)texture.width/(float)screenWidth;
            }else{
                scale = (float)texture.height/(float)screenHeight;
            }
        }

        //printf("scaled image based on %dx%d by %f\n",texture.width,texture.height,scale);
            ClearBackground(BLACK);
            if(show){
                //DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);
                //DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint)
                DrawTextureEx(texture,position,0.0f,scale,WHITE);
            }
            

            //DrawText("Congrats! You created your first window!", screenWidth/2, screenHeight/2, 20, RED);

        EndDrawing();
        //show = !show;
        //----------------------------------------------------------------------------------
    }
    UnloadTexture(texture); 
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}