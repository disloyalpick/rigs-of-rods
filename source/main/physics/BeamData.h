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

/// @file
/// @author Thomas Fischer
/// @date   30th of April 2010
/// @brief Core data structures for simulation.

#pragma once

/*
 A word of warning:
 RoR's performance is very sensitive to the ordering of the parameters in this
 structure (due to cache reasons). You can easily destroy RoR's performance if you put
 something in the wrong place. Unless you know what you are doing (do you come armed
 with a cache usage tracker?), add what you wish to the bottom of the structure.
*/

// The RoR required includes (should be included already)
#include "RoRPrerequisites.h"
#include "RoRnet.h"
#include "SlideNode.h"
#include "BeamConstants.h"

enum event_types {
    EVENT_NONE=0,
    EVENT_ALL,
    EVENT_AVATAR,
    EVENT_TRUCK,
    EVENT_AIRPLANE,
    EVENT_BOAT,
    EVENT_DELETE
};

enum hook_states {
    HOOK_LOCK=0,
    HOOK_UNLOCK,
    HOOK_TOGGLE,
    MOUSE_HOOK_TOGGLE,
};

/* Enumerations */
enum {
    BEAM_NORMAL,
    BEAM_HYDRO,
    BEAM_VIRTUAL,
    BEAM_MARKED,
    BEAM_INVISIBLE,
    BEAM_INVISIBLE_HYDRO
};

enum {
    SIMULATED,      //!< simulated (local) truck
    NETWORKED,      //!< not simulated (remote) truck
    SLEEPING,       //!< sleeping (local) truck
    INVALID         //!< not simulated and not updated via the network (e.g. size differs from expected)
};

enum {
    UNLOCKED,       //!< lock not locked
    PREUNLOCK,      //!< preunlocking, inter truck beam deletion in progress
    PRELOCK,        //!< prelocking, attraction forces in action
    LOCKED          //!< lock locked.
};
enum {
    NOT_DRIVEABLE,  //!< not drivable at all
    TRUCK,          //!< its a truck
    AIRPLANE,       //!< its an airplane
    BOAT,           //!< its a boat
    MACHINE,        //!< its a machine
    AI,             //!< machine controlled by an Artificial Intelligence
};
enum {
    DRY,            //!< node is dry
    DRIPPING,       //!< node is dripping
    WET             //!< node is wet
};
enum {
    NOSHOCK,        //!< not a shock
    SHOCK1,         //!< shock1
    SHOCK2,         //!< shock2
    SUPPORTBEAM,    //!<
    ROPE            //!<
};
enum blinktype {
    BLINK_NONE,     //!<
    BLINK_LEFT,     //!<
    BLINK_RIGHT,    //!<
    BLINK_WARN      //!<
};

enum {
    HYDRO_FLAG_SPEED        = BITMASK(1),
    HYDRO_FLAG_DIR          = BITMASK(2),
    HYDRO_FLAG_AILERON      = BITMASK(3),
    HYDRO_FLAG_RUDDER       = BITMASK(4),
    HYDRO_FLAG_ELEVATOR     = BITMASK(5),
    HYDRO_FLAG_REV_AILERON  = BITMASK(6),
    HYDRO_FLAG_REV_RUDDER   = BITMASK(7),
    HYDRO_FLAG_REV_ELEVATOR = BITMASK(8),
};

enum {
    ANIM_FLAG_AIRSPEED      = BITMASK(1),
    ANIM_FLAG_VVI           = BITMASK(2),
    ANIM_FLAG_ALTIMETER     = BITMASK(3),
    ANIM_FLAG_AOA           = BITMASK(4),
    ANIM_FLAG_FLAP          = BITMASK(5),
    ANIM_FLAG_AIRBRAKE      = BITMASK(6),
    ANIM_FLAG_ROLL          = BITMASK(7),
    ANIM_FLAG_PITCH         = BITMASK(8),
    ANIM_FLAG_THROTTLE      = BITMASK(9),
    ANIM_FLAG_RPM           = BITMASK(10),
    ANIM_FLAG_ACCEL         = BITMASK(11),
    ANIM_FLAG_BRAKE         = BITMASK(12),
    ANIM_FLAG_CLUTCH        = BITMASK(13),
    ANIM_FLAG_TACHO         = BITMASK(14),
    ANIM_FLAG_SPEEDO        = BITMASK(15),
    ANIM_FLAG_PBRAKE        = BITMASK(16),
    ANIM_FLAG_TURBO         = BITMASK(17),
    ANIM_FLAG_SHIFTER       = BITMASK(18),
    ANIM_FLAG_AETORQUE      = BITMASK(19),
    ANIM_FLAG_AEPITCH       = BITMASK(20),
    ANIM_FLAG_AESTATUS      = BITMASK(21),
    ANIM_FLAG_TORQUE        = BITMASK(22),
    ANIM_FLAG_HEADING       = BITMASK(23),
    ANIM_FLAG_DIFFLOCK      = BITMASK(24),
    ANIM_FLAG_STEERING      = BITMASK(25),
    ANIM_FLAG_EVENT         = BITMASK(26),
    ANIM_FLAG_AILERONS      = BITMASK(27),
    ANIM_FLAG_ARUDDER       = BITMASK(28),
    ANIM_FLAG_BRUDDER       = BITMASK(29),
    ANIM_FLAG_BTHROTTLE     = BITMASK(30),
    ANIM_FLAG_PERMANENT     = BITMASK(31),
    ANIM_FLAG_ELEVATORS     = BITMASK(32),
};

enum {
    ANIM_MODE_ROTA_X        = BITMASK(1),
    ANIM_MODE_ROTA_Y        = BITMASK(2),
    ANIM_MODE_ROTA_Z        = BITMASK(3),
    ANIM_MODE_OFFSET_X      = BITMASK(4),
    ANIM_MODE_OFFSET_Y      = BITMASK(5),
    ANIM_MODE_OFFSET_Z      = BITMASK(6),
    ANIM_MODE_AUTOANIMATE   = BITMASK(7),
    ANIM_MODE_NOFLIP        = BITMASK(8),
    ANIM_MODE_BOUNCE        = BITMASK(9),
};

enum {
    SHOCK_FLAG_NORMAL			= BITMASK(1),
    SHOCK_FLAG_INVISIBLE		= BITMASK(2),
    SHOCK_FLAG_LACTIVE			= BITMASK(3),
    SHOCK_FLAG_RACTIVE			= BITMASK(4),
    SHOCK_FLAG_ISSHOCK2			= BITMASK(5),
    SHOCK_FLAG_SOFTBUMP			= BITMASK(6),
    SHOCK_FLAG_ISTRIGGER		= BITMASK(7),
    SHOCK_FLAG_TRG_BLOCKER		= BITMASK(8),
    SHOCK_FLAG_TRG_CMD_SWITCH	= BITMASK(9),
    SHOCK_FLAG_TRG_CMD_BLOCKER	= BITMASK(10),
    SHOCK_FLAG_TRG_BLOCKER_A	= BITMASK(11),
    SHOCK_FLAG_TRG_HOOK_UNLOCK 	= BITMASK(12),
    SHOCK_FLAG_TRG_HOOK_LOCK   	= BITMASK(13),
    SHOCK_FLAG_TRG_CONTINUOUS	= BITMASK(14),
    SHOCK_FLAG_TRG_ENGINE		= BITMASK(15)
};

enum {
    TRG_ENGINE_CLUTCH    = 0,
    TRG_ENGINE_BRAKE     = 1,
    TRG_ENGINE_ACC       = 2,
    TRG_ENGINE_RPM       = 3,
    TRG_ENGINE_SHIFTUP   = 4,
    TRG_ENGINE_SHIFTDOWN = 5 
};

enum {
    DEFAULT_DETACHER_GROUP  = 0, // default for detaching beam group
};

enum {
    NOWHEEL,
    WHEEL_DEFAULT,
    WHEEL_2,
    WHEEL_FLEXBODY
};

/* some info holding arrays */
static const float flapangles[6] = {0.f, -0.07f, -0.17f, -0.33f, -0.67f, -1.f};

/* basic structures */

#include "datatypes/node_t.h"
#include "datatypes/shock_t.h"

struct collcab_rate_t
{
    int rate;     // remaining amount of physics cycles to be skipped
    int distance; // distance (in physics cycles) to the previous collision check
};

#include "datatypes/beam_t.h"

struct soundsource_t
{
    SoundScriptInstance* ssi;
    int nodenum;
    int type;
};

struct contacter_t
{
    int nodeid;
};

struct rigidifier_t
{
    node_t* a;
    node_t* b;
    node_t* c;
    float k;
    float d;
    float alpha;
    float lastalpha;
    beam_t *beama;
    beam_t *beamc;
};

#include "datatypes/wheel_t.h"

struct hook_t
{
    int locked;
    int group;
    int lockgroup;
    bool lockNodes;
    bool selflock;
    bool autolock;
    bool nodisable;
    float maxforce;
    float lockrange;
    float lockspeed;
    float timer;
    float timer_preset;
    node_t *hookNode;
    node_t *lockNode;
    beam_t *beam;
    Beam *lockTruck;
};

struct ropable_t
{
    node_t *node;
    int group;
    bool multilock;
    bool in_use;
};

struct rope_t
{
    int locked;
    int group;
    beam_t *beam;
    node_t *lockedto;
    ropable_t *lockedto_ropable;
    Beam *lockedtruck;
};


struct tie_t
{
    Beam* locked_truck;
    beam_t *beam;
    ropable_t *lockedto;
    int group;
    bool tied;
    bool tying;
    float commandValue;
};


struct wing_t
{
    FlexAirfoil *fa;
    Ogre::SceneNode *cnode;
};

struct command_t
{
    int commandValueState;
    float commandValue;
    float triggerInputValue;
    float playerInputValue;
    bool trigger_cmdkeyblock_state;  //!< identifies blocked F-commands for triggers
    std::vector<int> beams;
    std::vector<int> rotators;
    Ogre::String description;
};

struct rotator_t
{
    int nodes1[4];
    int nodes2[4];
    int axis1; //!< rot axis
    int axis2;
    float angle;
    float rate;
    float force;
    float tolerance;
    float rotatorEngineCoupling;
    bool rotatorNeedsEngine;
};

struct flare_t
{
    int noderef;
    int nodex;
    int nodey;
    float offsetx;
    float offsety;
    float offsetz;
    Ogre::SceneNode *snode;
    Ogre::BillboardSet *bbs;
    Ogre::Light *light;
    char type;
    int controlnumber;
    bool controltoggle_status;
    float blinkdelay;
    float blinkdelay_curr;
    bool blinkdelay_state;
    float size;
    bool isVisible;
};

/**
* SIM-CORE; Prop = an object mounted on vehicle chassis.
*/
struct prop_t
{
    int noderef;
    int nodex;
    int nodey;
    float offsetx;
    float offsety;
    float offsetz;
    float rotaX;
    float rotaY;
    float rotaZ;
    float orgoffsetX;
    float orgoffsetY;
    float orgoffsetZ;
    Ogre::Quaternion rot;
    Ogre::SceneNode *scene_node; //!< The pivot scene node (parented to root-node).
    Ogre::SceneNode *wheel; //!< Special prop: custom steering wheel for dashboard
    Ogre::Vector3 wheelpos; //!< Special prop: custom steering wheel for dashboard
    int mirror;             //<! Special prop: rear view mirror {0 = disabled, -1 = right, 1 = left}
    char beacontype;        //<! Special prop: beacon {0 = none, 'b' = user-specified, 'r' = red, 'p' = police lightbar, 'L'/'R'/'w' - aircraft wings}

    // formerly named "bbs"
    Ogre::BillboardSet *beacon_flares_billboard_system[4];

    // formerly named bbsnode
    Ogre::SceneNode *beacon_flare_billboard_scene_node[4];

    // formerly named "light"
    Ogre::Light *beacon_light[4];

    // formerly named "brate"
    float beacon_light_rotation_rate[4]; //<! Radians per second
    
    // formerly named "bpos"
    float beacon_light_rotation_angle[4]; //<! Radians
    

    int pale;               //!< Is this a pale? (Boolean {0/1})
    int spinner;            //!< Is this a spinprop? (Boolean {0/1})
    float animratio[10]; //!< A coefficient for the animation, prop degree if used with mode: rotation and propoffset if used with mode: offset.
    int animFlags[10];
    int animMode[10];
    float animOpt3[10]; //!< Various purposes
    float animOpt5[10];
    int animKey[10];
    int animKeyState[10];
    int lastanimKS[10];
    Ogre::Real wheelrotdegree;
    int cameramode; //!< Visibility control {-2 = always, -1 = 3rdPerson only, 0+ = cinecam index}
    MeshObject *mo;
    MeshObject *wheelmo;

    struct {
        float lower_limit;  //!< The lower limit for the animation
        float upper_limit;  //!< The upper limit for the animation
    } constraints[10];
};

struct exhaust_t
{
    int emitterNode;
    int directionNode;
    char material[256];
    float factor;
    bool isOldFormat; //!< False if defined in 'exhausts' section, true if defined in 'nodes' by 'x'/'y' flag.
    Ogre::SceneNode *smokeNode;
    Ogre::ParticleSystem* smoker;
};


struct cparticle_t
{
    int emitterNode;
    int directionNode;
    bool active;
    Ogre::SceneNode *snode;
    Ogre::ParticleSystem* psys;
};

#include "datatypes/rig_t.h"


// some non-beam structs


struct collision_box_t
{
    //absolute collision box
    Ogre::Vector3 lo; //!< absolute collision box
    Ogre::Vector3 hi; //!< absolute collision box
    bool refined;
    //rotation
    Ogre::Quaternion rot; //!< rotation
    Ogre::Quaternion unrot; //!< rotation
    //center of rotation
    Ogre::Vector3 center; //!< center of rotation
    //relative collision box
    Ogre::Vector3 relo; //!< relative collision box
    Ogre::Vector3 rehi; //!< relative collision box
    //self rotation
    bool selfrotated;
    Ogre::Vector3 selfcenter;
    Ogre::Quaternion selfrot;
    Ogre::Quaternion selfunrot;
    int eventsourcenum;
    bool virt;
    bool camforced;
    Ogre::Vector3 campos;
    int event_filter;
    bool enabled;
    Ogre::Vector3 ilo, ihi;
};

struct ground_model_t
{
    float va;                       //!< adhesion velocity
    float ms;                       //!< static friction coefficient
    float mc;                       //!< sliding friction coefficient
    float t2;                       //!< hydrodynamic friction (s/m)
    float vs;                       //!< stribeck velocity (m/s)
    float alpha;                    //!< steady-steady
    float strength;                 //!< ground strength

    float fluid_density;            //!< Density of liquid
    float flow_consistency_index;   //!< general drag coefficient

    //! if flow_behavior_index<1 then liquid is Pseudoplastic (ketchup, whipped cream, paint)
    //! if =1 then liquid is Newtoni'an fluid
    //! if >1 then liquid is Dilatant fluid (less common)
    float flow_behavior_index;

    
    float solid_ground_level;       //!< how deep the solid ground is
    float drag_anisotropy;          //!< Upwards/Downwards drag anisotropy

    int fx_type;
    Ogre::ColourValue fx_colour;
    char name[256];
    char basename[256];
    char particle_name[256];

    int fx_particle_amount;         //!< amount of particles

    float fx_particle_min_velo;     //!< minimum velocity to display sparks
    float fx_particle_max_velo;     //!< maximum velocity to display sparks
    float fx_particle_fade;         //!< fade coefficient
    float fx_particle_timedelta;    //!< delta for particle animation
    float fx_particle_velo_factor;  //!< velocity factor
    float fx_particle_ttl;
};

struct authorinfo_t
{
    int id;
    Ogre::String type;
    Ogre::String name;
    Ogre::String email;
};
