 /******************************************************************************
 *
 * Module: PORT
 *
 * File Name: PORT.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - PORT Driver
 *
 * Author: Ahmed Gamal
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif
   
/*variable to store the port status */
static volatile uint8  PORT_Status = PORT_NOT_INITIALIZED;




/************************************************************************************
* Service Name: Port_GetPortPinID
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): PinID - pin index in the config array
* Parameters (inout): None
* Parameters (out): None
* Return value: portpin id
* Description: Function to return the port number and pin id in the port
* Note: non AUTOSAR function
************************************************************************************/
static uint8 Port_GetPortPinID(uint8 PinID){
  switch(PinID){
    case PORT_PIN_01:                     return(0xB6);break;
    case PORT_PIN_04:                     return(0xB7);break;
    case PORT_PIN_05:                     return(0xF4);break;
    case PORT_PIN_06:                     return(0xE3);break;
    case PORT_PIN_07:                     return(0xE2);break;
    case PORT_PIN_08:                     return(0xE1);break;
    case PORT_PIN_09:                     return(0xE0);break;
    case PORT_PIN_10:                     return(0xD7);break;
    case PORT_PIN_13:                     return(0xC7);break;
    case PORT_PIN_14:                     return(0xC6);break;
    case PORT_PIN_15:                     return(0xC5);break;
    case PORT_PIN_16:                     return(0xC4);break;
    case PORT_PIN_17:                     return(0xA0);break;
    case PORT_PIN_18:                     return(0xA1);break;
    case PORT_PIN_19:                     return(0xA2);break;
    case PORT_PIN_20:                     return(0xA3);break;
    case PORT_PIN_21:                     return(0xA4);break;
    case PORT_PIN_22:                     return(0xA5);break;
    case PORT_PIN_23:                     return(0xA6);break;
    case PORT_PIN_24:                     return(0xA7);break;
    case PORT_PIN_28:                     return(0xF0);break;
    case PORT_PIN_29:                     return(0xF1);break;
    case PORT_PIN_30:                     return(0xF2);break;
    case PORT_PIN_31:                     return(0xF3);break;
    case PORT_PIN_43:                     return(0xD4);break;
    case PORT_PIN_44:                     return(0xD5);break;
    case PORT_PIN_45:                     return(0xB0);break;
    case PORT_PIN_46:                     return(0xB1);break;
    case PORT_PIN_47:                     return(0xB2);break;
    case PORT_PIN_48:                     return(0xB3);break;
    case PORT_PIN_49:                     return(0xC3);break;
    case PORT_PIN_50:                     return(0xC2);break;
    case PORT_PIN_51:                     return(0xC1);break;
    case PORT_PIN_52:                     return(0xC0);break;
    case PORT_PIN_53:                     return(0xD6);break;
    case PORT_PIN_57:                     return(0xB5);break;
    case PORT_PIN_58:                     return(0xB4);break;
    case PORT_PIN_59:                     return(0xE4);break;
    case PORT_PIN_60:                     return(0xE5);break;
    case PORT_PIN_61:                     return(0xD0);break;
    case PORT_PIN_62:                     return(0xD1);break;
    case PORT_PIN_63:                     return(0xD2);break;
    case PORT_PIN_64:                     return(0xD3);break;
    
  }
  return 0x00 ;
}

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port driver module.
************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr ){
  
  /* variable to track the error */
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{       error = TRUE;
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_Init_SID,
		     PORT_E_PARAM_CONFIG);
	}
	else{
          /*do nothing*/
        }
#endif  
        /* run the service if there is no error (or the DEV error detect is off )*/
        if(error == FALSE){
        /*counter for the for loop looping on the array of config structures*/
        uint8 counter = 0 ;
        /* variable to store the portpin ID in the MCU */
        uint8 Port_Pin_Num = 0 ;
        /*variable to store the PORT ID in the MCU*/
        uint8 Port_Num = 0 ;
        /*variable to store the Pin ID in the MCU */
        uint8 Pin_Num = 0 ;
        /* mask to get the port ID */
        uint8 Port_Mask =  0xF0 ;
        /* mask to get the pin ID */
        uint8 Pin_Mask =  0x0F ;
        /*flag to check if the pins are jtag pins */
         uint8 JTAG_FLAG = 0 ;
          
          
          for(counter = 0; counter < Port_NumberOfPortPins; counter++ ){
            /*clear jtag flag*/
            JTAG_FLAG = 0 ;
            Port_Pin_Num = Port_GetPortPinID((*ConfigPtr).Channels[counter].Pin_ID);
            Port_Num = Port_Pin_Num & Port_Mask ;
            Pin_Num = Port_Pin_Num & Pin_Mask ;
            volatile uint32 * GPIO_PORT_DATA_REG = NULL_PTR;
            volatile uint32 * GPIO_PORT_DIR_REG = NULL_PTR;
            volatile uint32 * GPIO_PORT_AFSEL_REG = NULL_PTR;
            volatile uint32 * GPIO_PORT_PUR_REG = NULL_PTR;
            volatile uint32 * GPIO_PORT_PDR_REG = NULL_PTR;
            volatile uint32 * GPIO_PORT_DEN_REG = NULL_PTR;
            volatile uint32 * GPIO_PORT_LOCK_REG = NULL_PTR;
            volatile uint32 * GPIO_PORT_CR_REG = NULL_PTR;
            volatile uint32 * GPIO_PORT_AMSEL_REG = NULL_PTR;
            volatile uint32 * GPIO_PORT_PCTL_REG = NULL_PTR;
            
            
            
            switch(Port_Num){
              /* Port A */
              case 0xA0:
                GPIO_PORT_DATA_REG = GPIO_PORTA_DATA_REG;
                GPIO_PORT_DIR_REG = GPIO_PORTA_DIR_REG;
                GPIO_PORT_AFSEL_REG = GPIO_PORTA_AFSEL_REG;
                GPIO_PORT_PUR_REG = GPIO_PORTA_PUR_REG;
                GPIO_PORT_PDR_REG = GPIO_PORTA_PDR_REG;
                GPIO_PORT_DEN_REG = GPIO_PORTA_DEN_REG;
                GPIO_PORT_LOCK_REG = GPIO_PORTA_LOCK_REG;
                GPIO_PORT_CR_REG = GPIO_PORTA_CR_REG;
                GPIO_PORT_AMSEL_REG = GPIO_PORTA_AMSEL_REG;
                GPIO_PORT_PCTL_REG = GPIO_PORTA_PCTL_REG;
                break;
                
              /*Port B */  
              case 0xB0:
                GPIO_PORT_DATA_REG = GPIO_PORTB_DATA_REG;
                GPIO_PORT_DIR_REG = GPIO_PORTB_DIR_REG;
                GPIO_PORT_AFSEL_REG = GPIO_PORTB_AFSEL_REG;
                GPIO_PORT_PUR_REG = GPIO_PORTB_PUR_REG;
                GPIO_PORT_PDR_REG = GPIO_PORTB_PDR_REG;
                GPIO_PORT_DEN_REG = GPIO_PORTB_DEN_REG;
                GPIO_PORT_LOCK_REG = GPIO_PORTB_LOCK_REG;
                GPIO_PORT_CR_REG = GPIO_PORTB_CR_REG;
                GPIO_PORT_AMSEL_REG = GPIO_PORTB_AMSEL_REG;
                GPIO_PORT_PCTL_REG = GPIO_PORTB_PCTL_REG;
                break;
                
              /*Port c */  
              case 0xC0:
                GPIO_PORT_DATA_REG = GPIO_PORTC_DATA_REG;
                GPIO_PORT_AFSEL_REG = GPIO_PORTC_AFSEL_REG;
                GPIO_PORT_PUR_REG = GPIO_PORTC_PUR_REG;
                GPIO_PORT_PDR_REG = GPIO_PORTC_PDR_REG;
                GPIO_PORT_DEN_REG = GPIO_PORTC_DEN_REG;
                GPIO_PORT_LOCK_REG = GPIO_PORTC_LOCK_REG;
                GPIO_PORT_CR_REG = GPIO_PORTC_CR_REG;
                GPIO_PORT_AMSEL_REG = GPIO_PORTC_AMSEL_REG;
                GPIO_PORT_PCTL_REG = GPIO_PORTC_PCTL_REG;
                break;
              
              /*Port D */  
              case 0xD0:
                 GPIO_PORT_DATA_REG = GPIO_PORTD_DATA_REG;
                GPIO_PORT_AFSEL_REG = GPIO_PORTD_AFSEL_REG;
                GPIO_PORT_PUR_REG = GPIO_PORTD_PUR_REG;
                GPIO_PORT_PDR_REG = GPIO_PORTD_PDR_REG;
                GPIO_PORT_DEN_REG = GPIO_PORTD_DEN_REG;
                GPIO_PORT_LOCK_REG = GPIO_PORTD_LOCK_REG;
                GPIO_PORT_CR_REG = GPIO_PORTD_CR_REG;
                GPIO_PORT_AMSEL_REG = GPIO_PORTD_AMSEL_REG;
                GPIO_PORT_PCTL_REG = GPIO_PORTD_PCTL_REG;
                break;
                
              /*Port E */  
              case 0xE0:
                 GPIO_PORT_DATA_REG = GPIO_PORTE_DATA_REG;
                GPIO_PORT_AFSEL_REG = GPIO_PORTE_AFSEL_REG;
                GPIO_PORT_PUR_REG = GPIO_PORTE_PUR_REG;
                GPIO_PORT_PDR_REG = GPIO_PORTE_PDR_REG;
                GPIO_PORT_DEN_REG = GPIO_PORTE_DEN_REG;
                GPIO_PORT_LOCK_REG = GPIO_PORTE_LOCK_REG;
                GPIO_PORT_CR_REG = GPIO_PORTE_CR_REG;
                GPIO_PORT_AMSEL_REG = GPIO_PORTE_AMSEL_REG;
                GPIO_PORT_PCTL_REG = GPIO_PORTE_PCTL_REG;
                break;
                
              /*Port F */  
              case 0xF0:
                GPIO_PORT_DATA_REG = GPIO_PORTF_DATA_REG;
                GPIO_PORT_DIR_REG = GPIO_PORTF_DIR_REG;
                GPIO_PORT_AFSEL_REG = GPIO_PORTF_AFSEL_REG;
                GPIO_PORT_PUR_REG = GPIO_PORTF_PUR_REG;
                GPIO_PORT_PDR_REG = GPIO_PORTF_PDR_REG;
                GPIO_PORT_DEN_REG = GPIO_PORTF_DEN_REG;
                GPIO_PORT_LOCK_REG = GPIO_PORTF_LOCK_REG;
                GPIO_PORT_CR_REG = GPIO_PORTF_CR_REG;
                GPIO_PORT_AMSEL_REG = GPIO_PORTF_AMSEL_REG;
                GPIO_PORT_PCTL_REG = GPIO_PORTF_PCTL_REG;
                break;
               
            }
            
          
           /*start of configuration */
            /*unlock the locked pins */
            if( ((Port_Num == 0xD0) && (Pin_Num == 7)) || ((Port_Num == 0xF0) && (Pin_Num == 0)) ) /* PD7 or PF0 */
            {
            *GPIO_PORT_LOCK_REG = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
            SET_BIT(* GPIO_PORT_CR_REG, Pin_Num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
            }
            else if( (Port_Num == 0xC0) && (Pin_Num <= 3) ) /* PC0 to PC3 */
            {
              /* set jtag flag to be true */
              JTAG_FLAG = 1 ;
            /* Do Nothing ...  this is the JTAG pins */
               
            }
            else
            {
            /* Do Nothing ... No need to unlock the commit register for this pin */
            }
            
            if(JTAG_FLAG == 0 ){
          /*configure the pin direction */
           switch((*ConfigPtr).Channels[counter].PORT_PIN_DIRECTION){
                      /* the pin is configured as input pin  */
                      case PORT_PIN_IN:
                          /*configure the pin as input pin*/
                          CLEAR_BIT(*GPIO_PORT_DIR_REG,Pin_Num);
                          /*Enable the internal pull up resistance */
                          if((*ConfigPtr).Channels[counter].Pin_Resistance == PORT_PIN_RESISTANCE_PULL_UP){
                            SET_BIT(*GPIO_PORT_PUR_REG,Pin_Num);
                          }
                          /*Enable the internal pull down resistance */
                          else if((*ConfigPtr).Channels[counter].Pin_Resistance == PORT_PIN_RESISTANCE_PULL_DOWN){
                            SET_BIT(*GPIO_PORT_PDR_REG,Pin_Num);
                          }
                          /*disable both the internal pull up and pull down resistance */
                          else{
                            CLEAR_BIT(*GPIO_PORT_PUR_REG,Pin_Num);
                            CLEAR_BIT(*GPIO_PORT_PDR_REG,Pin_Num);
                          }
                          break;
                        /*the pin is configured as output pin */  
                        case PORT_PIN_OUT:
                          /*configure the pin as output pin*/
                          SET_BIT(*GPIO_PORT_DIR_REG,Pin_Num);
                          /* put the intial output value */
                          { uint32 temp ;
                            temp =  (CLEAR_BIT(*GPIO_PORT_DATA_REG,Pin_Num)) | (((*ConfigPtr).Channels[counter].PORT_PIN_LEVEL_VALUE << Pin_Num) & (1 << Pin_Num ));
                            *GPIO_PORT_DATA_REG = temp ;
                          }
                          break;
            }
            /*configure the pin Analog or digital */
           switch((*ConfigPtr).Channels[counter].Port_PinIntialType){
                      /* the pin is configured as analog pin  */
                      case ANALOG_PIN:
                          CLEAR_BIT(*GPIO_PORT_DEN_REG,Pin_Num);
                          SET_BIT(*GPIO_PORT_AMSEL_REG,Pin_Num);
                          break;
                        /*the pin is configured as digital pin */  
                        case DIGITAL_PIN:
                          SET_BIT(*GPIO_PORT_DEN_REG,Pin_Num);
                          CLEAR_BIT(*GPIO_PORT_AMSEL_REG,Pin_Num);
                          break;
            }
            
            /*configure the pin function */
            switch((*ConfigPtr).Channels[counter].PORT_PIN_INITIAL_MODE){
                /* the pin intital mode is Digital input output */
                case PORT_PIN_MODE_DIO :
                    /* clear the bit in GPIO alternate function select register to configure the bit as DIO pin */
                    CLEAR_BIT(*GPIO_PORT_AFSEL_REG,Pin_Num);
                    
                    /* configure the pin direction */
                    break;
                  /* the pin intital mode is analog digital converter */ 
                default:
                  /*Enable the alternative function */
                  SET_BIT(*GPIO_PORT_AFSEL_REG,Pin_Num);
                  
                  break;
            }
            /* set the mode number in the CTL reg */
            *GPIO_PORT_PCTL_REG=((*GPIO_PORT_PCTL_REG&(~(Port_Mask<<(Pin_Num*4))))|((((*ConfigPtr).Channels[counter].PORT_PIN_INITIAL_MODE)&(Port_Mask))<<(Pin_Num*4)));
                
          }
          
          else{
           /*do nothing */
          }
          /*end of configuration */
          
          
          
          }
          /* change the port status to intitialized */    
          PORT_Status = PORT_INITIALIZED;
        }
        else{
        /*do nothing */
        }
      
        
}

/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - port pin ID number
                   Direction - port pin direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the port pin direction
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction ){
    
    /* variable to track the error */
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    
  /*check if the port driver is not intiallized */
    if(PORT_Status == PORT_NOT_INITIALIZED){
      error = TRUE;
      Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinDirection_SID,
		     PORT_E_UNINIT);
      
    }
    else{
    /* do nothing */
    }
    
    /*check if the pin ID passed is correct */
    if(Pin >= Port_NumberOfPortPins){
      error = TRUE ;
       Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinDirection_SID,
		     PORT_E_PARAM_PIN);
    
    }
    else{
      /*do nothing */
    }
    
    /* check if the port pin is not configured as changeable */
    if(Port_Configuration.Channels[Pin].PORT_PIN_DIRECTION_CHANGEABLE == STD_OFF){
      error = TRUE;
      Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinDirection_SID,
		     PORT_E_DIRECTION_UNCHANGEABLE);
    }
    else{
    /*do nothing*/
    }
#endif
    /* run the service if there is no error (or the DEV error detect is off )*/
    if(error == FALSE){
        /* variable to store the portpin ID in the MCU */
        uint8 Port_Pin_Num = 0 ;
        /*variable to store the PORT ID in the MCU*/
        uint8 Port_Num = 0 ;
        /*variable to store the Pin ID in the MCU */
        uint8 Pin_Num = 0 ;
        /* mask to get the port ID */
        uint8 Port_Mask =  0xF0 ;
        /* mask to get the pin ID */
        uint8 Pin_Mask =  0x0F ;
        Port_Pin_Num = Port_GetPortPinID(Pin);
        Port_Num = Port_Pin_Num & Port_Mask ;
        Pin_Num = Port_Pin_Num & Pin_Mask ;
        volatile uint32 * GPIO_PORT_DIR_REG = NULL_PTR;
                    switch(Port_Num){
                      
                      case 0xA0:
                          /*set the PTR to port A*/
                          GPIO_PORT_DIR_REG = GPIO_PORTA_DIR_REG;
                          
                          break;
                      case 0xB0:
                          /*set the PTR to port B*/
                          GPIO_PORT_DIR_REG = GPIO_PORTB_DIR_REG;
                          break;
                      case 0xC0:
                          /*set the PTR to port C*/
                          GPIO_PORT_DIR_REG = GPIO_PORTC_DIR_REG;
                          break;
                      case 0xD0:
                          /*set the PTR to port D*/
                         GPIO_PORT_DIR_REG = GPIO_PORTD_DIR_REG;
                          break;
                       case 0xE0:
                          /*set the PTR to port E*/
                         GPIO_PORT_DIR_REG = GPIO_PORTE_DIR_REG;
                          break;
                       case 0xF0:
                          /*set the PTR to port F*/
                          GPIO_PORT_DIR_REG = GPIO_PORTF_DIR_REG;
                          break;
                             
                       
                    }
                    if(Direction == PORT_PIN_IN){
                          CLEAR_BIT(*GPIO_PORT_DIR_REG,Pin_Num);
                          }
                          /*the pin is configured as output pin */ 
                    else if(Direction == PORT_PIN_OUT){
                            SET_BIT(*GPIO_PORT_DIR_REG,Pin_Num);
                    }
    
    
    }





}
#endif
/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to refresh port direction
************************************************************************************/
void Port_RefreshPortDirection( void ){
/* variable to track the error */
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    
  /*check if the port driver is not intiallized */
    if(PORT_Status == PORT_NOT_INITIALIZED){
      error = TRUE;
      Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_RefreshPortDirection_SID,
		     PORT_E_UNINIT);
      
    }
    else{
    /* do nothing */
    }
#endif
        if(error == FALSE){
        /*counter for the for loop looping on the array of config structures*/
        uint8 counter = 0 ;
        /* variable to store the portpin ID in the MCU */
        uint8 Port_Pin_Num = 0 ;
        /*variable to store the PORT ID in the MCU*/
        uint8 Port_Num = 0 ;
        /*variable to store the Pin ID in the MCU */
        uint8 Pin_Num = 0 ;
        /* mask to get the port ID */
        uint8 Port_Mask =  0xF0 ;
        /* mask to get the pin ID */
        uint8 Pin_Mask =  0x0F ;
        /* run the service if there is no error (or the DEV error detect is off )*/
        
          /* set the gloable ptr with the address of the config structure*/
          
          for(counter = 0; counter < Port_NumberOfPortPins; counter++ ){
                    Port_Pin_Num = Port_GetPortPinID(Port_Configuration.Channels[counter].Pin_ID);
                    Port_Num = Port_Pin_Num & Port_Mask ;
                    Pin_Num = Port_Pin_Num & Pin_Mask ;
                    volatile uint32 * GPIO_PORT_DIR_REG = NULL_PTR;
                    switch(Port_Num){
                      
                      case 0xA0:
                          /*set the PTR to port A*/
                          GPIO_PORT_DIR_REG = GPIO_PORTA_DIR_REG;
                          
                          break;
                      case 0xB0:
                          /*set the PTR to port B*/
                          GPIO_PORT_DIR_REG = GPIO_PORTB_DIR_REG;
                          break;
                      case 0xC0:
                          /*set the PTR to port C*/
                          GPIO_PORT_DIR_REG = GPIO_PORTC_DIR_REG;
                          break;
                      case 0xD0:
                          /*set the PTR to port D*/
                         GPIO_PORT_DIR_REG = GPIO_PORTD_DIR_REG;
                          break;
                       case 0xE0:
                          /*set the PTR to port E*/
                         GPIO_PORT_DIR_REG = GPIO_PORTE_DIR_REG;
                          break;
                       case 0xF0:
                          /*set the PTR to port F*/
                          GPIO_PORT_DIR_REG = GPIO_PORTF_DIR_REG;
                          break;
                             
                             
                       
                    }
                    /*configure the pin as input pin*/
                    if(Port_Configuration.Channels[counter].PORT_PIN_DIRECTION == PORT_PIN_IN){
                            CLEAR_BIT(*GPIO_PORT_DIR_REG,Pin_Num);
                     }
                          /*the pin is configured as output pin */ 
                     else if(Port_Configuration.Channels[counter].PORT_PIN_DIRECTION == PORT_PIN_OUT){
                            SET_BIT(*GPIO_PORT_DIR_REG,Pin_Num);
    
          }
    
    }


    
        }





}
/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - pointer to where to store the version 
                                  information of this module 
* Return value: None
* Description: Function to Return the version information of this module
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo ){
/* variable to track the error */
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    
  /*check if the port driver is not intiallized */
    if(PORT_Status == PORT_NOT_INITIALIZED){
      error = TRUE;
      Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_GetVersionInfo_SID,
		     PORT_E_UNINIT);
      
    }
    else{
    /* do nothing */
    }
    /*check if the API is called with a NULL pointer parameter */
    if(versioninfo == NULL_PTR){
      error = TRUE;
      Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_GetVersionInfo_SID,
		     PORT_E_PARAM_POINTER);
    }
    else{
    /*do nothing*/
    }
    
#endif
    /* run the service if there is no error (or the DEV error detect is off )*/
    if(error == FALSE){
    
    
                /* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    
    
    
    }




}
#endif
/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - port pin ID number
                   Mode - new port pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None 
* Return value: None
* Description: Function to set the port pin mode
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode ){
/* variable to track the error */
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    
  /*check if the port driver is not intiallized */
    if(PORT_Status == PORT_NOT_INITIALIZED){
      error = TRUE;
      Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_SID,
		     PORT_E_UNINIT);
      
    }
    else{
    /* do nothing */
    }
    /*check if the pin ID passed is correct */
    if(Pin>=Port_NumberOfPortPins){
      error = TRUE ;
       Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_SID,
		     PORT_E_PARAM_PIN);
    
    }
    else{
      /*do nothing */
    }
    
    /* check if the port pin is not configured as changeable */
    if(Port_Configuration.Channels[Pin].PORT_PIN_MODE_CHANGEABLE == STD_OFF){
      error = TRUE;
      Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_SID,
		     PORT_E_MODE_UNCHANGEABLE);
    }
    else{
    /*do nothing*/
    }
    /*check if the mode passed is not valid*/
    if(Mode >= PORT_Modes_supported){
    error = TRUE;
      Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, Port_SetPinMode_SID,
		     PORT_E_PARAM_INVALID_MODE);
    
    }
    
    else{
    /*do nothing*/
    }
    
#endif
    /* run the service if there is no error (or the DEV error detect is off )*/
    if(error == FALSE){
    
    
        /* variable to store the portpin ID in the MCU */
        uint8 Port_Pin_Num = 0 ;
        /*variable to store the PORT ID in the MCU*/
        uint8 Port_Num = 0 ;
        /*variable to store the Pin ID in the MCU */
        uint8 Pin_Num = 0 ;
        /* mask to get the port ID */
        uint8 Port_Mask =  0xF0 ;
        /* mask to get the pin ID */
        uint8 Pin_Mask =  0x0F ;
        Port_Pin_Num = Port_GetPortPinID(Pin);
        Port_Num = Port_Pin_Num & Port_Mask ;
        Pin_Num = Port_Pin_Num & Pin_Mask ;
        volatile uint32 * GPIO_PORT_PCTL_REG = NULL_PTR;
        volatile uint32 * GPIO_PORT_AFSEL_REG = NULL_PTR;
         volatile uint32 * GPIO_PORT_DEN_REG = NULL_PTR;
        volatile uint32 * GPIO_PORT_AMSEL_REG = NULL_PTR;
        
        switch(Port_Num){
        case 0xA0:
            GPIO_PORT_PCTL_REG = GPIO_PORTA_PCTL_REG;
            GPIO_PORT_AFSEL_REG =GPIO_PORTA_AFSEL_REG;
            GPIO_PORT_DEN_REG = GPIO_PORTA_DEN_REG;
            GPIO_PORT_AMSEL_REG = GPIO_PORTA_AMSEL_REG;

            break;
        case 0xB0:
            GPIO_PORT_PCTL_REG = GPIO_PORTB_PCTL_REG;
            GPIO_PORT_AFSEL_REG =GPIO_PORTB_AFSEL_REG;
            GPIO_PORT_DEN_REG = GPIO_PORTB_DEN_REG;
            GPIO_PORT_AMSEL_REG = GPIO_PORTB_AMSEL_REG;

            break;
        case 0xC0:
            GPIO_PORT_PCTL_REG = GPIO_PORTC_PCTL_REG;
            GPIO_PORT_AFSEL_REG =GPIO_PORTC_AFSEL_REG;
            GPIO_PORT_DEN_REG = GPIO_PORTC_DEN_REG;
            GPIO_PORT_AMSEL_REG = GPIO_PORTC_AMSEL_REG;

            break;
        case 0xD0:
            GPIO_PORT_PCTL_REG = GPIO_PORTD_PCTL_REG;
            GPIO_PORT_AFSEL_REG =GPIO_PORTD_AFSEL_REG;
            GPIO_PORT_DEN_REG = GPIO_PORTD_DEN_REG;
            GPIO_PORT_AMSEL_REG = GPIO_PORTD_AMSEL_REG;

            break;
        case 0xE0:
            GPIO_PORT_PCTL_REG = GPIO_PORTE_PCTL_REG;
            GPIO_PORT_AFSEL_REG =GPIO_PORTE_AFSEL_REG;
            GPIO_PORT_DEN_REG = GPIO_PORTE_DEN_REG;
            GPIO_PORT_AMSEL_REG = GPIO_PORTE_AMSEL_REG;

            break;
        case 0xF0:
            GPIO_PORT_PCTL_REG = GPIO_PORTF_PCTL_REG;
            GPIO_PORT_AFSEL_REG =GPIO_PORTF_AFSEL_REG;
            GPIO_PORT_DEN_REG = GPIO_PORTF_DEN_REG;
            GPIO_PORT_AMSEL_REG = GPIO_PORTF_AMSEL_REG;

            break;
        }
             /*configure the pin Analog or digital */
        switch(Port_Configuration.Channels[Pin].Port_PinIntialType){
                      /* the pin is configured as analog pin  */
                      case ANALOG_PIN:
                          CLEAR_BIT(*GPIO_PORT_DEN_REG,Pin_Num);
                          SET_BIT(*GPIO_PORT_AMSEL_REG,Pin_Num);
                          break;
                        /*the pin is configured as digital pin */  
                        case DIGITAL_PIN:
                          SET_BIT(*GPIO_PORT_DEN_REG,Pin_Num);
                          CLEAR_BIT(*GPIO_PORT_AMSEL_REG,Pin_Num);
                          break;
            }
   
        switch(Mode){
                /* the pin intital mode is Digital input output */
                case PORT_PIN_MODE_DIO :
                    /* clear the bit in GPIO alternate function select register to configure the bit as DIO pin */
                    CLEAR_BIT(*GPIO_PORT_AFSEL_REG,Pin_Num);
                    
                    
                    /* configure the pin direction */
                    break;
                  /* the pin intital mode is analog digital converter */ 
                default:
                  /*Enable the alternative function */
                  SET_BIT(*GPIO_PORT_AFSEL_REG,Pin_Num);
                  
                  
                  break;
            }
            /* set the mode number in the CTL reg */
            *GPIO_PORT_PCTL_REG=((*GPIO_PORT_PCTL_REG&(~(Port_Mask<<(Pin_Num*4))))|(((Mode)&(Port_Mask))<<(Pin_Num*4)));
       
    
    
    }

    


}
#endif