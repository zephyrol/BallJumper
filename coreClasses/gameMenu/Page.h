
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Map.cpp
 * Author: Morgenthaler S
 *
 * Created on 28 avril 2020, 18:56
 */

#ifndef PAGE_H
#define PAGE_H
#include "Label.h"

class Page
{
public:
    //--CONSTRUCTORS & DESTRUCTORS--//
    Page( const std::vector<std::shared_ptr<const Label> >& labels,
          const std::map<std::shared_ptr<const Label>,
            std::shared_ptr<const Page> >& bridges = {},
          const std::shared_ptr<const Page>& parent = nullptr,
          bool visibleOnParent  = false,
          float height = 1.f);

    
    //-------CONST METHODS--------//
    const std::vector<std::shared_ptr<const Label> >& labels()            const;
    const std::map<std::shared_ptr<const Label>, std::shared_ptr<const Page> >& 
                                                      bridges()           const;
    const std::shared_ptr<const Page>&                parent()            const;
    bool                                              visibleOnParent()   const;

    std::shared_ptr<const Page>                       child(float x, float y)
                                                                          const;
    float                                             height()            const;
private:

    //--------ATTRIBUTES-----------//
    const std::vector<std::shared_ptr<const Label> >  _labels;
    const std::map<std::shared_ptr<const Label>, std::shared_ptr<const Page> >
                                                      _bridges;
    const std::shared_ptr<const Page>                 _parent;
    const bool                                        _visibleOnParent;
    const float                                       _height;
    float                                             _posY;
};

#endif // PAGE_H
