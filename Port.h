 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Ahmed Gamal
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 *  */
#define PORT_VENDOR_ID    (1000U)

/* PORT Module Id */
#define PORT_MODULE_ID    (124U)

/* PORT Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for PORT Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and PORT Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* PORT Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PORT_Cfg.h does not match the expected version"
#endif

/* Software Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PORT_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for PORT init*/
#define Port_Init_SID                  (uint8)0x00

/* Service ID for PORT set pin direction*/
#define Port_SetPinDirection_SID       (uint8)0x01

/* Service ID for PORT refresh port direction */
#define Port_RefreshPortDirection_SID  (uint8)0x02

/* Service ID for PORT get version information */
#define Port_GetVersionInfo_SID        (uint8)0x03

/* Service ID for PORT set pin mode */
#define Port_SetPinMode_SID            (uint8)0x04



/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* Invalid port pinID requested  */
#define PORT_E_PARAM_PIN                 (uint8)0x0A

/* Port pin is configured as unchangable */
#define PORT_E_DIRECTION_UNCHANGEABLE    (uint8)0x0B

/* API port init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG              (uint8)0x0C

/*API Port_SetPinMode service called when mode is invalid */
#define PORT_E_PARAM_INVALID_MODE        (uint8)0x0D

/* API Port_SetPinMode service called when mode is unchangeable*/
#define PORT_E_MODE_UNCHANGEABLE         (uint8)0x0E

/*API service called without module initialization*/
#define PORT_E_UNINIT                   (uint8)0x0F
   
 /*APIs called with a Null pointer */
#define PORT_E_PARAM_POINTER            (uint8)0x10   
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* type defination for the PORT_pinType */
typedef uint8 Port_PinType;

/* type defination for the Port_PinDirectionType */
typedef enum{
PORT_PIN_IN,PORT_PIN_OUT
}Port_PinDirectionType;
   
/* type defination for the Port_PinModeType */
typedef uint8 Port_PinModeType;




/* type defination for the Port_configPin structure */
typedef struct{  
   Port_PinType Pin_ID;
   Port_PinModeType PORT_PIN_INITIAL_MODE;
   uint8 Port_PinIntialType; /* analog or digital */
   Port_PinDirectionType PORT_PIN_DIRECTION;
   uint8 PORT_PIN_LEVEL_VALUE;
   uint8 PORT_PIN_DIRECTION_CHANGEABLE; 
   uint8 PORT_PIN_MODE_CHANGEABLE;
   uint8 Pin_Resistance;
   
   
   
   
}Port_ConfigPin;
   
typedef struct{  
   Port_ConfigPin Channels[Port_NumberOfPortPins];
   
   
}Port_ConfigType;
   
 
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function for PORT initialization API*/
void Port_Init( const Port_ConfigType* ConfigPtr );

/* Function for PORT set pin Direction API*/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif


/* Function for PORT refresh port direction API */
void Port_RefreshPortDirection( void );

/* Function for PORT get version info API*/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif


/* Function for PORT set pin mode API */
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
#endif


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by PORT and other modules */
extern const Port_ConfigType Port_Configuration;
#endif /* PORT_H */
