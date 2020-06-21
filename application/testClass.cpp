/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   testClass.cpp
 * Author: Morgenthaler S
 * 
 * Created on 2 novembre 2019, 11:17
 */

#include <fstream>
#include <istream>
#include <sstream>
#include "testClass.h"
#include <initializer_list>


testClass::testClass(): _window(nullptr),
_player(),
_controller(_player)
{
    if( !glfwInit() )
    {
      std::cerr << "Failed to init glfw" << std::endl;
    }
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    
    /*_window = glfwCreateWindow(RESOLUTION_X,RESOLUTION_Y,
                                "JumperBall",glfwGetPrimaryMonitor(),
           nullptr);*/
    _window = glfwCreateWindow( RESOLUTION_X,RESOLUTION_Y,
                                "JumperBall",nullptr, nullptr);
    
    int widthWindow;
    int heightWindow;
    glfwGetFramebufferSize(_window ,&widthWindow ,&heightWindow);
    
    Utility::windowResolutionX = widthWindow;
    Utility::windowResolutionY = heightWindow;

    if( _window == nullptr ){
    std::cerr << "Failed to open GLFW window" << std::endl;
    glfwTerminate();
    }
    
    glfwMakeContextCurrent(_window);
    if (!gladLoadGL()) {
        std::cerr << "Unable to load OpenGL functions !" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!TextRendering::initFreeTypeAndFont()) {
        exit(EXIT_FAILURE);
    } 

}

void testClass::runController(Rendering& r, const std::shared_ptr<Ball>& b,
                              Camera& c) {

    auto before = JumperBallTypesMethods::getTimePointMSNow();
    unsigned int counter = 0;
    
    _player.statut(Player::Statut::INGAME);
    _controller.assignBall(b);
    
    glfwSetInputMode(_window,GLFW_STICKY_KEYS,GL_TRUE) ;
    while (glfwGetKey(_window,GLFW_KEY_ESCAPE) != GLFW_PRESS
           && glfwWindowShouldClose(_window) == 0 ) {
        

        b->update();
        c.follow(*b);
        
        if( glfwGetKey(_window,GLFW_KEY_ENTER) == GLFW_PRESS ||
           glfwGetKey(_window,GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            _controller.interactionButtons(Controller::Button::Validate,
                                    Controller::Status::Pressed);
        }
        
        if(glfwGetKey(_window,GLFW_KEY_RIGHT) == GLFW_PRESS ||
           glfwGetKey(_window,GLFW_KEY_L) == GLFW_PRESS) {
            _controller.interactionButtons(Controller::Button::Right,
                                    Controller::Status::Pressed);
        }
        
        if(glfwGetKey(_window,GLFW_KEY_LEFT) == GLFW_PRESS ||
           glfwGetKey(_window,GLFW_KEY_H) == GLFW_PRESS) {
            _controller.interactionButtons(Controller::Button::Left,
                                    Controller::Status::Pressed);
        }
        
        if(glfwGetKey(_window,GLFW_KEY_UP) == GLFW_PRESS ||
           glfwGetKey(_window,GLFW_KEY_K) == GLFW_PRESS) {
            _controller.interactionButtons(Controller::Button::Up,
                                    Controller::Status::Pressed);
        }
        
        if(glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_1 ) == GLFW_PRESS) {
            double posX, posY;
            glfwGetCursorPos(_window,&posX ,&posY);
            posX = posX / static_cast<double>(RESOLUTION_X);
            posY = posY / static_cast<double>(RESOLUTION_Y);

            _controller.interactionMouse(Controller::Status::Pressed,
                                         static_cast<float>(posX), 
                                         static_cast<float>(posY));
        }
        
        if(glfwGetKey(_window,GLFW_KEY_ENTER) == GLFW_RELEASE ||
           glfwGetKey(_window,GLFW_KEY_SPACE) == GLFW_RELEASE)
        {
            _controller.interactionButtons(Controller::Button::Validate,
                                    Controller::Status::Released);
        }
        
        if(glfwGetKey(_window,GLFW_KEY_RIGHT) == GLFW_RELEASE ||
           glfwGetKey(_window,GLFW_KEY_L) == GLFW_RELEASE) {
            _controller.interactionButtons(Controller::Button::Right,
                                    Controller::Status::Released);
        }
        
        if(glfwGetKey(_window,GLFW_KEY_LEFT) == GLFW_RELEASE ||
           glfwGetKey(_window,GLFW_KEY_H) == GLFW_RELEASE) {
            _controller.interactionButtons(Controller::Button::Left,
                                    Controller::Status::Released);
        }
        
        if(glfwGetKey(_window,GLFW_KEY_UP) == GLFW_RELEASE ||
           glfwGetKey(_window,GLFW_KEY_K) == GLFW_RELEASE) {
            _controller.interactionButtons(Controller::Button::Up,
                                    Controller::Status::Released);
        }
        
        if(glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_1 ) == GLFW_RELEASE) {
            double posX, posY;
            glfwGetCursorPos(_window,&posX ,&posY);
            posX = posX / static_cast<double>(RESOLUTION_X);
            posY = posY / static_cast<double>(RESOLUTION_Y);
            
            _controller.interactionMouse(Controller::Status::Released,
                                         static_cast<float>(posX), 
                                         static_cast<float>(posY));
        }
        
        
        b->update();
        c.follow(*b);
        
        r.render();
        
        glfwSwapInterval(1);
        glfwSwapBuffers(_window);
        
        glfwPollEvents();
        
        counter++;
        auto after = JumperBallTypesMethods::getTimePointMSNow();
        auto diff = after - before;
        const std::chrono::duration<float> durationFloatDifference= diff;
        float diffF = durationFloatDifference.count();
        if (diffF > 1.f) {
            before = after;
            std::cout << counter << " FPS"  << std::endl;
            counter = 0;
        }
    }
}


void testClass::runMenu(Rendering& r, Ball& b, Camera& c, Map& m) {

    //Menu 1
    std::shared_ptr<const MessageLabel> label =
        std::make_shared<const MessageLabel>(
            Utility::xScreenToPortrait(1.f), 0.1f,
            JumperBallTypes::vec2f{0.5f,0.8f},
            "Jumper Ball");
    std::shared_ptr<const MessageLabel> label2 = 
        std::make_shared<const MessageLabel> (
            Utility::xScreenToPortrait(0.4f), 0.05f,
            JumperBallTypes::vec2f{0.5f,0.6f},
            "Play");
    std::shared_ptr<const MessageLabel> label3 = 
        std::make_shared<const MessageLabel> (
            Utility::xScreenToPortrait(0.6f), 0.05f,
            JumperBallTypes::vec2f{0.5f,0.4f},
            "Store");
    std::shared_ptr<const MessageLabel> label4 = 
        std::make_shared<const MessageLabel> (
            Utility::xScreenToPortrait(0.4f), 0.05f,
            JumperBallTypes::vec2f{0.5f,0.2f},
            "Exit");
    
    //Menu 2
    std::vector<std::shared_ptr<const Label> > labelsPage2;
    
    std::shared_ptr<const MessageLabel> labelLevels =
    std::make_shared<const MessageLabel>
    (Utility::xScreenToPortrait(1.  ),
     0.2f, JumperBallTypes::vec2f{0.5f, 1.f - 0.1f},
     "Levels");
    labelsPage2.push_back(labelLevels);
    
    //constexpr float offsetBox = 0.02f;
    for (size_t i = 0; i < 15; ++i) {
        
        std::string sNumber;
        if( i < 10 ) {
            sNumber.append("0");
        }
        sNumber.append(std::to_string(i+1));
        
        
        /*std::shared_ptr<const BoxLabel> boxLabelLevels =
        std::make_shared<const BoxLabel>
        (   Utility::xScreenToPortrait(.2f), 0.1f,
         JumperBallTypes::vec2f{.5f - Utility::xScreenToPortrait(.5f)
            + Utility::xScreenToPortrait(.1f + (i%3) * .4f), 1.f-(0.3f + i/3 * 0.3f)-offsetBox});
        labelsPage2.push_back(boxLabelLevels);*/
        
        std::shared_ptr<const MessageLabel> labelLevel =
        std::make_shared<const MessageLabel>
        (Utility::xScreenToPortrait(.2f), 0.1f,
         JumperBallTypes::vec2f{ .5f - Utility::xScreenToPortrait(.5f)
            + Utility::xScreenToPortrait(.1f + (i%3) * .4f),
            1.f-(0.3f + i/3 * 0.3f)}, sNumber);
        

        labelsPage2.push_back(labelLevel);
    }

    //Menu 2
    std::shared_ptr<const BoxLabel> labelBox =
    std::make_shared<const BoxLabel>(0.5f, 0.1f,
                                     JumperBallTypes::vec2f{0.5f,0.8f} );
    

    const std::vector<std::shared_ptr<const Label> > labelsPage1
    {label, label2, label3, label4};


    std::map<std::shared_ptr<const Label>,
        std::shared_ptr<const Page> > bridgesPage1 ;
    
    std::map<std::shared_ptr<const Label>,
        std::shared_ptr<const Page> > bridgesPage2 ;

    const std::shared_ptr<Page> page1 =
        std::make_shared<Page> (labelsPage1, nullptr, false);
    
    const std::shared_ptr<Page> page2 =
        std::make_shared<Page> (labelsPage2, page1, false);
    
    page1->addBridge(label2, page2);

    Menu menu(page2);


    glfwSetInputMode(_window,GLFW_STICKY_KEYS,GL_TRUE) ;
    while (glfwGetKey(_window,GLFW_KEY_ESCAPE) != GLFW_PRESS
           && glfwWindowShouldClose(_window) == 0 ) {
        
        b.update();
        c.follow(m);
        
        r.render();
        menu.render();
        
        glfwSwapInterval(1);
        glfwSwapBuffers(_window);
        
        glfwPollEvents();
        
    }
}

testClass::~testClass() {
    glfwTerminate();
    TextRendering::clearFreeTypeRessources();
}
