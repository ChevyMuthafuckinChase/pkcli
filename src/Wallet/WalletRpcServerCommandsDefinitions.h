#pragma once
#include "CryptoNoteProtocol/CryptoNoteProtocolDefinitions.h"
#include "CryptoNoteCore/CryptoNoteBasic.h"
#include "crypto/hash.h"
#include "Rpc/CoreRpcServerCommandsDefinitions.h"
#include "WalletRpcServerErrorCodes.h"

namespace Tools
{
	namespace wallet_rpc
	{
		using CryptoNote::ISerializer;

#define WALLET_RPC_STATUS_OK      "OK"
#define WALLET_RPC_STATUS_BUSY    "BUSY"

		struct COMMAND_RPC_GET_BALANCE
		{
			typedef CryptoNote::EMPTY_STRUCT request;

			struct response
			{
				uint64_t locked_amount;
				uint64_t available_balance;
				uint64_t balance;            //<! \deprecated Use locked_amount + available_balance
				uint64_t unlocked_balance;   //<! \deprecated Use available_balance

				void serialize(ISerializer& s) {
					KV_MEMBER(locked_amount)
						KV_MEMBER(available_balance)
						KV_MEMBER(balance)
						KV_MEMBER(unlocked_balance)
				}
			};
		};

		struct transfer_destination
		{
			uint64_t amount;
			std::string address;
			std::string message;

			void serialize(ISerializer& s) {
				KV_MEMBER(amount)
					KV_MEMBER(address)
					KV_MEMBER(message)
			}
		};

		struct TransferMessage {
			std::string address;
			std::string message;

			void serialize(ISerializer& s) {
				KV_MEMBER(address)
					KV_MEMBER(message)
			}
		};

		struct COMMAND_RPC_TRANSFER
		{
			struct request
			{
				std::list<transfer_destination> destinations;
				uint64_t fee;
				uint64_t mixin;
				uint64_t unlock_time;
				std::string payment_id;
				std::list<TransferMessage> messages;
				uint64_t ttl = 0;

				void serialize(ISerializer& s) {
					KV_MEMBER(destinations)
						KV_MEMBER(fee)
						KV_MEMBER(mixin)
						KV_MEMBER(unlock_time)
						KV_MEMBER(payment_id)
						KV_MEMBER(messages)
						KV_MEMBER(ttl)
				}
			};

			struct response
			{
				std::string tx_hash;

				void serialize(ISerializer& s) {
					KV_MEMBER(tx_hash)
				}
			};
		};

		struct COMMAND_RPC_STORE
		{
			typedef CryptoNote::EMPTY_STRUCT request;
			typedef CryptoNote::EMPTY_STRUCT response;
		};

		struct transaction_messages {
			std::string tx_hash;
			uint64_t tx_id;
			uint32_t block_height;
			uint64_t timestamp;
			std::list<std::string> messages;

			void serialize(ISerializer& s) {
				KV_MEMBER(tx_hash);
				KV_MEMBER(tx_id);
				KV_MEMBER(block_height);
				KV_MEMBER(timestamp);
				KV_MEMBER(messages);
			}
		};
 struct COMMAND_RPC_CREATE_INTEGRATED
    {
      struct request
      {
        std::string payment_id;
        std::string address;      
        void serialize(ISerializer& s) {
          KV_MEMBER(payment_id)
          KV_MEMBER(address)         
        }
      };
      struct response
      {
        std::string integrated_address;
        void serialize(ISerializer& s) 
        {
          KV_MEMBER(integrated_address)
        }
    };
  };

		struct COMMAND_RPC_GET_MESSAGES {
			struct request {
				uint64_t first_tx_id = 0;
				uint32_t tx_limit = std::numeric_limits<uint32_t>::max();

				void serialize(ISerializer& s) {
					KV_MEMBER(first_tx_id);
					KV_MEMBER(tx_limit);
				}
			};

			struct response {
				uint64_t total_tx_count;
				std::list<transaction_messages> tx_messages;

				void serialize(ISerializer& s) {
					KV_MEMBER(total_tx_count);
					KV_MEMBER(tx_messages);
				}
			};
		};

		struct payment_details
		{
			std::string tx_hash;
			uint64_t amount;
			uint64_t block_height;
			uint64_t unlock_time;

			void serialize(ISerializer& s) {
				KV_MEMBER(tx_hash)
					KV_MEMBER(amount)
					KV_MEMBER(block_height)
					KV_MEMBER(unlock_time)
			}
		};

		struct COMMAND_RPC_GET_PAYMENTS
		{
			struct request
			{
				std::string payment_id;

				void serialize(ISerializer& s) {
					KV_MEMBER(payment_id)
				}
			};

			struct response
			{
				std::list<payment_details> payments;

				void serialize(ISerializer& s) {
					KV_MEMBER(payments)
				}
			};
		};

		struct Transfer {
			uint64_t time;
			bool output;
			std::string transactionHash;
			uint64_t amount;
			uint64_t fee;
			std::string paymentId;
			std::string address;
			uint64_t blockIndex;
			uint64_t unlockTime;

			void serialize(ISerializer& s) {
				KV_MEMBER(time)
					KV_MEMBER(output)
					KV_MEMBER(transactionHash)
					KV_MEMBER(amount)
					KV_MEMBER(fee)
					KV_MEMBER(paymentId)
					KV_MEMBER(address)
					KV_MEMBER(blockIndex)
					KV_MEMBER(unlockTime)
			}
		};

		struct COMMAND_RPC_GET_TRANSFERS {
			typedef CryptoNote::EMPTY_STRUCT request;

			struct response {
				std::list<Transfer> transfers;

				void serialize(ISerializer& s) {
					KV_MEMBER(transfers)
				}
			};
		};

		struct COMMAND_RPC_GET_HEIGHT {
			typedef CryptoNote::EMPTY_STRUCT request;

			struct response {
				uint64_t height;

				void serialize(ISerializer& s) {
					KV_MEMBER(height)
				}
			};
		};

  struct COMMAND_RPC_GET_OUTPUTS
  {
    typedef CryptoNote::EMPTY_STRUCT request;
    struct response
    {
      size_t num_unlocked_outputs;
      void serialize(ISerializer& s) {
        KV_MEMBER(num_unlocked_outputs)
      }
    };
  };
		struct COMMAND_RPC_RESET {
			typedef CryptoNote::EMPTY_STRUCT request;
			typedef CryptoNote::EMPTY_STRUCT response;
		};
	}
}
