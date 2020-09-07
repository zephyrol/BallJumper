/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Menu.h
 * Author: Morgenthaler S
 *
 * Created on 10 mai 2020, 15:47
 */

#ifndef MENU_H
#define MENU_H
#include <gameMenu/Page.h>
#include "TextRendering.h"
#include "BoxRendering.h"

class Menu
{
public:
    Menu(const Page_sptr& rootPage,
         const Page_sptr& pausePage,
         const Page_sptr& successPage,
         const Page_sptr& failurePage);

    //void render() const;
    Page_sptr currentPage();
    CstPage_sptr currentPage() const;
    void currentPage(const Page_sptr &page);

    void update(bool isPressed, float screenPosY);

    void rootPageAsCurrentPage();
    void pausePageAsCurrentPage();
    void successPageAsCurrentPage();
    void failurePageAsCurrentPage();

    CstPage_sptr rootPage() const;
    CstPage_sptr pausePage() const;
    CstPage_sptr successPage() const;
    CstPage_sptr failurePage() const;

    static std::shared_ptr<Menu> getJumperBallMenu(size_t currentLevel);

private:
    const Page_sptr _rootPage;
    const Page_sptr _pausePage;
    const Page_sptr _successPage;
    const Page_sptr _failurePage;
    
    Page_sptr _currentPage;

    static float getHeight (const Page_sptr& page);
};

#endif /* MENU_H */

