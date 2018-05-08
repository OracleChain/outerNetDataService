/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include "outerNetDataService.hpp"

void OuterNetDataService::storeRequestWeb(const requestweb & parrequestweb){
    RequestWebTable tfs(contractCode, admin);
    auto ite = tfs.rbegin();

    uint64_t idnew;
    if(ite == tfs.rend()){
        idnew = 0;
    }else{
        idnew = ite->primary_key()+1;
    }

    requestwebt newrequestwebt;
    newrequestwebt.id = idnew;
    newrequestwebt.copyFrom(parrequestweb);
    tfs.emplace(parrequestweb.from, [&](auto &s){
        s = newrequestwebt;
    });
}

/**
 *  The init() and apply() methods must have C calling convention so that the blockchain can lookup and
 *  call these methods.
 */

extern "C" {

    /// The apply method implements the dispatch of events to this contract
    void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
        switch(action)
        {
            case N(add):
            {
                OuterNetDataService().storeRequestWeb( eosio::unpack_action_data<requestweb>() );
                break;
            }

        default:
            break;
    }

} // extern "C"
}
