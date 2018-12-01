/*
    This source file is part of Rigs of Rods
    Copyright 2005-2012 Pierre-Michel Ricordel
    Copyright 2007-2012 Thomas Fischer
    Copyright 2013-2017 Petr Ohlidal & contributors

    For more information, see http://www.rigsofrods.org/

    Rigs of Rods is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3, as
    published by the Free Software Foundation.

    Rigs of Rods is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Rigs of Rods. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "RoRPrerequisites.h"

#include "mygui/BaseLayout.h"

class SurveyMapTextureCreator;

ATTRIBUTE_CLASS_LAYOUT(SurveyMapManager, "MapControl.layout");

class SurveyMapManager : public wraps::BaseLayout
{
public:

    SurveyMapManager(Ogre::Vector2 terrain_size);
    ~SurveyMapManager();

    SurveyMapEntity* createMapEntity(Ogre::String type);
    void deleteMapEntity(SurveyMapEntity* entity);

    void windowResized();

    void setVisibility(bool visible) { mMainWidget->setVisible(visible); };
    bool getVisibility() { return mMainWidget->getVisible(); };

    void Update(Ogre::Real dt, Actor* curr_truck);
    void UpdateMapEntity(SurveyMapEntity* e, Ogre::String caption, Ogre::Vector3 pos, float rot, int state, bool visible);

    static Ogre::String getTypeByDriveable(int driveable);

protected:

    enum SurveyMapTypes
    {
        SURVEY_MAP_NONE,
        SURVEY_MAP_SMALL,
        SURVEY_MAP_BIG,
        SURVEY_MAP_END
    };

    Ogre::Vector2 mTerrainSize;
    Ogre::Vector2 mPlayerPosition;

    Ogre::Real mMapZoom;
    Ogre::Vector2 mMapSize;
    Ogre::Vector2 mMapCenter;

    ATTRIBUTE_FIELD_WIDGET_NAME(SurveyMapManager, mMapTexture, "mMapTexture");

    MyGUI::StaticImage* mMapTexture;

    SurveyMapTextureCreator* mMapTextureCreator;

    std::set<SurveyMapEntity*> mMapEntities;
    bool mMapEntitiesVisible;
    int mMapMode;

    void updateMap();
    void updateWindowPosition();
    void toggleMapView();
    void setMapZoom(Ogre::Real zoom);
    void setMapZoomRelative(Ogre::Real delta);
    void setPlayerPosition(Ogre::Vector2 position);
    void setWindowPosition(int x, int y, float size);
};


