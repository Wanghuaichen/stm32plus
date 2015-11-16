/*
 * Can.h
 *
 *  Created on: 2015. nov. 10.
 *      Author: elektroman
 */

#pragma once
#include "config/debug.h"

namespace stm32plus {


	class Can {
		protected:
		  CAN_TypeDef *_peripheralAddress;
		  CAN_InitTypeDef _init;
		protected:
		  Can(CAN_TypeDef *peripheralAddress);



		public:

		  void enablePeripheral() const;
		  void disablePeripheral() const;
		  bool send(const uint32_t ID, const uint8_t IDE, const uint8_t RTR, const uint8_t DLC, uint8_t* data  );
		  bool send(CanTxMsg& Msg);


		  operator CAN_TypeDef *();
		  operator CAN_InitTypeDef *();

	};

	/**
	 * Constructor
	 */

	inline Can::Can(CAN_TypeDef *peripheralAddress)
	   : _peripheralAddress(peripheralAddress) {


	}


	inline void Can::enablePeripheral() const {
	}

	inline void Can::disablePeripheral() const {
	}

	inline Can::operator CAN_TypeDef *(){
		return _peripheralAddress;
	}

	inline Can::operator CAN_InitTypeDef *() {
		return &_init;
	}




	inline bool Can::send(const uint32_t ID, const uint8_t IDE, const uint8_t RTR, const uint8_t DLC, uint8_t* data  ) {
		CanTxMsg Msg;
		Msg.IDE=IDE;
		Msg.RTR = RTR;
		Msg.DLC = DLC;
		Msg.ExtId = ID;

		for(uint8_t i=0; i<DLC;i++)
			Msg.Data[i]=data[i];



		if (CAN_TxStatus_NoMailBox != CAN_Transmit(_peripheralAddress,&Msg))
			return true;
		else
			return false;
	}



	inline bool Can::send(CanTxMsg& Msg) {

		if (CAN_TxStatus_NoMailBox != CAN_Transmit(_peripheralAddress,&Msg))
			return true;
		else
			return false;
	}



}  // namespace stm32plus
