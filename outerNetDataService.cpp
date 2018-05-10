/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include "outerNetDataService.hpp"

void OutNetDataSer::storeWebRequest(const webrequest & parrequestweb){
    ReqWebTable tfs(contractCode, admin);
    auto ite = tfs.rbegin();

    uint64_t idnew;
    if(ite == tfs.rend()){
        idnew = 0;
    }else{
        idnew = ite->primary_key()+1;
    }

    web newweb;
    newweb.id = idnew;
    newweb.copyFrom(parrequestweb);
    tfs.emplace(parrequestweb.from, [&](auto &s){
        s = newweb;
    });
}

void OutNetDataSer::storeWebResult(const webresult & parwebresult){

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
            case N(addwebreq):
            {
                OutNetDataSer().storeWebRequest(eosio::unpack_action_data<webrequest>());
                break;
            }
            case N(addwebres):
            {
                OutNetDataSer().storeWebResult(eosio::unpack_action_data<webresult>());
                break;
            }

        default:
            break;
    }

} // extern "C"
}
