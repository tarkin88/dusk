void
togglesticky(const Arg *arg)
{
	Workspace *ws = selws;
	if (!ws->sel)
		return;
	if (ISSTICKY(ws->sel))
		unsetsticky(ws->sel);
	else
		setsticky(ws->sel);
}

void
setsticky(Client *c)
{
	addflag(c, Sticky);

	stickyws->next = c->ws;
	stickyws->mon = c->ws->mon;
	detach(c);
	detachstack(c);
	attachx(c, AttachBottom, stickyws);
	attachstack(c);
	XRaiseWindow(dpy, c->win);
	arrange(stickyws->next);
}

void
unsetsticky(Client *c)
{
	removeflag(c, Sticky);
	detach(c);
	detachstack(c);
	attachx(c, AttachBottom, stickyws->next);
	attachstack(c);
	arrange(c->ws);
}