/* 
 * File:   Game.cpp
 * Author: igor
 * 
 * Created on 30-09-2017 г., 12:11
 */

#include "Game.hpp"
#include <iostream>

Game::Game():
mPlayer{std::make_unique<Player>()},
mWindow{sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE_OF_PROGRAM},
mBlock(sf::Vector2f(TILE_SIZE,TILE_SIZE))
{
     mSpriteSet.loadFromFile("resources/gfx/fang.png");
     mPlayer->setTexture(mSpriteSet);
}

Game::~Game() {
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    
    while (mWindow.isOpen())
    {
        processEvents();        
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > mTimePerFrame)
        {
            timeSinceLastUpdate -= mTimePerFrame;
            processEvents();
            updatePhase(mTimePerFrame.asSeconds());
        }
        renderPhase();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mWindow.close();
        }
    }
    mPlayer->handleUserInput();
}

void Game::updatePhase(float time)
{
    mPlayer->update(time, mMap);
}

void Game::renderPhase()
{
    mWindow.clear(sf::Color::Cyan);
    drawMap();
    mPlayer->draw(mWindow);
    mWindow.display();
}

void Game::drawMap()
{
    for (std::size_t y = 0; y < mMap.size(); ++y)
    {
        for (std::size_t x = 0; x < mMap[y].size(); ++x)
        {
            if(mMap[y][x] == 'X')
            {
                mBlock.setFillColor(sf::Color(127, 0, 0));
            }
            else if(mMap[y][x] == '0')
            {
                mBlock.setFillColor(sf::Color(127, 127, 0));
            }
            else
                continue;
            mBlock.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            mWindow.draw(mBlock);
        }
    }
}
