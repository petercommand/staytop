#include <X11/Xlib.h> 
#include <X11/Xatom.h>
#include <X11/Xmu/WinUtil.h>
#include <assert.h> 
#include <unistd.h>
#include <glib.h>
#include <string.h>
#include "send_message.h"
Display *disp;

static int change_state(unsigned long data0, char *data1)
{
    XEvent event;
    memset(&event, 0, sizeof(event));
    Window root_return, child_return;
    int root_x, root_y, win_x, win_y;
    unsigned int mask_return;
    XQueryPointer(disp, DefaultRootWindow(disp), &root_return, &child_return
		  , &root_x, &root_y, &win_x, &win_y, &mask_return);
    g_print("child window: %ld\n",child_return);
    g_print("x,y coord relative to root win: %d %d\n",root_x,root_y);
    long mask = SubstructureRedirectMask | SubstructureNotifyMask;
    event.xclient.type = ClientMessage;
    event.xclient.serial = 0;
    event.xclient.send_event = True;
    event.xclient.message_type = XInternAtom(disp, "_NET_WM_STATE", 0);
    event.xclient.window = child_return;
    event.xclient.format = 32;
    event.xclient.data.l[0] = data0;/* remove:0 add:1 toogle:2 */
    event.xclient.data.l[1] = XInternAtom(disp, data1, False);
    if(data0 == 1)
    {
      XSelectInput(disp, child_return, VisibilityChangeMask);
    }
    else
    {
      XSelectInput(disp, child_return, 0);
    }
    if (XSendEvent(disp, DefaultRootWindow(disp), False, mask, &event)) 
    {
      g_print("xsend success\n");
      XFlush (disp);
      return 0;
    }
    else 
    {
      g_print("xsend failed\n");
      XFlush (disp);
      return 1;
    }
}


int set_state()
{
  if(change_state(1,"_NET_WM_STATE_ABOVE") == 0)
    {
      return 0;
    }
  else
    {
      g_print("set state failed");
      return 1;
    }

}
int unset_state()
{
  if(change_state(0,"_NET_WM_STATE_ABOVE") == 0)
    {
      return 0;
    }
  else
    {
      g_print("set state failed");
      return 1;
    }
}

void raise_window_loop(){
  XEvent ev;
  while(1)
    {
      XNextEvent(disp, &ev);
      if(ev.type == VisibilityNotify)
	{
	  g_print("raising window: %ld", ev.xvisibility.window);
	  if(!XRaiseWindow(disp, ev.xvisibility.window))
	    {
	      g_print("XRaiseWindow error?\n");
	      
	    }

	}
    }

}
