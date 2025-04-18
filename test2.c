#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <sys/time.h>

// 'global' variables to store screen info
char *fbp = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
size_t screensize = 0;

// helper function for drawing - no more need to go mess with
// the main function when just want to change what to draw...
void draw() {

  int x, y, line;
  unsigned short *buffer;//todo switch to 2 byte data type
  struct timeval before, after, delta;

  buffer = (char *)malloc(screensize);
  //printf("Line length %i",finfo.line_length);

  for (y = 0; y < vinfo.yres; y++) {
    for (x = 0; x < vinfo.xres; x++) {
        long int location = 0;
        location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel / 8) +
            (y + vinfo.yoffset) * finfo.line_length;
        

      // color based on the 16th of the screen width
      //int c = 16 * x / vinfo.xres;
      //int c = 2016;//red
      //int c = 65535;
      unsigned short c = 0;
      if((x + vinfo.xoffset) * (vinfo.bits_per_pixel / 8) > 320){
        c = 65535; //should be white
      }
      else {
          c = 3425;
      }
      //else{
      //  c=63488; //should be red
      //}
      //printf("%d\n",x+line);
      //if (buffer[x + line] != 0) {
      //    //printf("repeat! %d\n",x+line);
      //}
      
    
      // call the helper function
      buffer[location] = c;
    }
  }

  gettimeofday(&before, NULL);  
  memcpy(fbp, buffer, screensize);
  gettimeofday(&after, NULL);
  timersub(&after, &before, &delta);

  printf("Display duration: %lu s, %lu us\n", delta.tv_sec, delta.tv_usec);

  free(buffer);
}

void sighdl(int sig)
{
  printf("SIGINT\n");
}

// application entry point
int main(int ac, char* av[])
{
  int fbfd = 0;
  //struct fb_var_screeninfo orig_vinfo;

  signal(SIGINT, sighdl);

  // Open the file for reading and writing
  fbfd = open("/dev/fb0", O_RDWR);
  if (!fbfd) {
    printf("Error: cannot open framebuffer device.\n");
    return(1);
  }
  printf("The framebuffer device was opened successfully.\n");

  // Get variable screen information
  if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
    printf("Error reading variable information.\n");
  }
  printf("Original %dx%d, %dbpp\n", vinfo.xres, vinfo.yres, 
         vinfo.bits_per_pixel );

  printf("xoffset :%d, yoffset: %d\n", vinfo.xoffset, vinfo.yoffset);

//   // Store for reset (copy vinfo to vinfo_orig)
//   memcpy(&orig_vinfo, &vinfo, sizeof(struct fb_var_screeninfo));

//   // Change variable info
//   vinfo.bits_per_pixel = 8;
//   if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &vinfo)) {
//     printf("Error setting variable information.\n");
//   }

  // Get fixed screen information
  if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
    printf("Error reading fixed information.\n");
  }

  // map fb to user mem 
  screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
  fbp = (char *)mmap(0, 
                    screensize, 
                    PROT_READ | PROT_WRITE, 
                    MAP_SHARED, 
                    fbfd, 
                    0);

  if ((int)fbp == -1) {
    printf("Failed to mmap.\n");
  }
  else {
    // draw...
    draw();

    // If no parameter, pause until a CTRL-C...
    if (ac == 1)
      pause();
  }

  // cleanup
  munmap(fbp, screensize);
//   if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &orig_vinfo)) {
//     printf("Error re-setting variable information.\n");
//   }
  close(fbfd);

  return 0;
  
}