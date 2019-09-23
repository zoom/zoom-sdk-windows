#ifndef  _CONTEXTMENU_H_
#define _CONTEXTMENU_H_
#include <windows.h>

#define  ITEM_MENU_RECORD    40001

class ParticipantPopMenu
{
public:
	ParticipantPopMenu();
	~ParticipantPopMenu();

	void PopMenu(HWND hwnd,int nX,int nY );
	void PopMenu(HWND hwnd,const POINT& pt);

	void SetUserID(unsigned int nUserID);
	void OnClickMenuItem(int nMenuItemId);

private:
	HMENU m_hPopMenu;
	unsigned int m_nUserID;
};
#endif