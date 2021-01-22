 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_ON)

/* Pre-compile option for presence of Port_SetPinDirection API */
#define PORT_SET_PIN_DIRECTION_API           (STD_ON)


/* Pre-compile option for presence of Port_SetPinMode API */
#define PORT_SET_PIN_MODE_API                (STD_ON)

/* define the number of pins in the portcontainer */
#define Port_NumberOfPortPins (43u)
/*define the number of modes in the MCU */
#define PORT_Modes_supported (11u)



/*define Default pin Dierction*/
#define PORT_DEFAULT_PIN_DIRECTION      (PORT_PIN_IN)
      
/* define defult pin direction changable option */
#define PORT_DEFULT_PIN_DIRECTION_CHANGEABLE (STD_ON)

/* define defult pin mode changable option */
#define PORT_DEFULT_PIN_MODE_CHANGEABLE (STD_ON)

   
/* define DIO mode number*/

#define PORT_PIN_MODE_DIO               (0u)
   
#define ANALOG_PIN                      (0)
#define DIGITAL_PIN                     (1)
   
/*define Default Pin mode*/
#define PORT_DEFAULT_PIN_MODE           (PORT_PIN_MODE_DIO)

/*define Default Pin Initial Value*/
#define PORT_DEFAULT_PIN_INITIAL_VALUE  (STD_LOW)

/*define pull up resistance */
#define PORT_PIN_RESISTANCE_PULL_UP     (2u)   

/*define pull up resistance */
#define PORT_PIN_RESISTANCE_PULL_DOWN     (1u)  
   
/*define pull up resistance */
#define PORT_PIN_RESISTANCE_OFF     (0u)   
   
/* define default pin internal resistance value */
#define PORT_PIN_DEFULT_RESISTANCE  (PORT_PIN_RESISTANCE_OFF)

/* define default pin internal pull down value */
#define PORT_DEFAULT_PIN_PULL_DOWN_VALUE  (STD_OFF)

   
   
   
   
/*Definition of pin index used in Port_PBcfg.c*/
#define PORT_PIN_01                     (uint8)(0)
#define PORT_PIN_04                     (uint8)(1)
#define PORT_PIN_05                     (uint8)(2)
#define PORT_PIN_06                     (uint8)(3)
#define PORT_PIN_07                     (uint8)(4)
#define PORT_PIN_08                     (uint8)(5)
#define PORT_PIN_09                     (uint8)(6)
#define PORT_PIN_10                     (uint8)(7)
#define PORT_PIN_13                     (uint8)(8)
#define PORT_PIN_14                     (uint8)(9)
#define PORT_PIN_15                     (uint8)(10)
#define PORT_PIN_16                     (uint8)(11)
#define PORT_PIN_17                     (uint8)(12)
#define PORT_PIN_18                     (uint8)(13)
#define PORT_PIN_19                     (uint8)(14)
#define PORT_PIN_20                     (uint8)(15)
#define PORT_PIN_21                     (uint8)(16)
#define PORT_PIN_22                     (uint8)(17)
#define PORT_PIN_23                     (uint8)(18)
#define PORT_PIN_24                     (uint8)(19)
#define PORT_PIN_28                     (uint8)(20)
#define PORT_PIN_29                     (uint8)(21)
#define PORT_PIN_30                     (uint8)(22)
#define PORT_PIN_31                     (uint8)(23)
#define PORT_PIN_43                     (uint8)(24)
#define PORT_PIN_44                     (uint8)(25)
#define PORT_PIN_45                     (uint8)(26)
#define PORT_PIN_46                     (uint8)(27)
#define PORT_PIN_47                     (uint8)(28)
#define PORT_PIN_48                     (uint8)(29)
#define PORT_PIN_49                     (uint8)(30)
#define PORT_PIN_50                     (uint8)(31)
#define PORT_PIN_51                     (uint8)(32)
#define PORT_PIN_52                     (uint8)(33)
#define PORT_PIN_53                     (uint8)(34)
#define PORT_PIN_57                     (uint8)(35)
#define PORT_PIN_58                     (uint8)(36)
#define PORT_PIN_59                     (uint8)(37)
#define PORT_PIN_60                     (uint8)(38)
#define PORT_PIN_61                     (uint8)(39)
#define PORT_PIN_62                     (uint8)(40)
#define PORT_PIN_63                     (uint8)(41)
#define PORT_PIN_64                     (uint8)(42)






#endif /* PORT_CFG_H */
