/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include "outerNetDataService.hpp"

void OutNetDataSer::storeWebRequest(const webrequest & parrequestweb){
    ReqWebTable tfs(contractCode, admin);
    require_auth(parrequestweb.from);
    auto ite = tfs.rbegin();

    uint64_t idnew;
    if(ite == tfs.rend())
    {
        idnew = 0;
    }
    else
    {
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
    require_auth(admin);
    ReqWebTable tfs(contractCode, admin);
    MultiIndexWebRes miwr(contractCode, admin);

    auto webIte = tfs.find(parwebresult.id);
    eosio_assert(webIte != tfs.end(), ID_NOT_EXIST);
    auto webresIte = miwr.find(parwebresult.id);
    if(webresIte == miwr.end()){
        miwr.emplace(admin, [&](auto &s){
            s.id =      parwebresult.id;
            s.webdata = parwebresult.webdata;
            s.errmsg = parwebresult.errmsg;
            //s.status = parwebresult.status;
        });
    }else{
        miwr.modify(webresIte, admin, [&](auto &s){
                   s.webdata = parwebresult.webdata;
                   s.errmsg = parwebresult.errmsg;
                   //s.status = parwebresult.status;
            });
    }
}

void OutNetDataSer::clearall(const clear & c){
    require_auth(admin);
    ReqWebTable tfs(contractCode, admin);
    auto ite = tfs.begin();
    while(ite!=tfs.end()){
        ite = tfs.erase(ite);
    }
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

            case N(clear):
            {
                OutNetDataSer().clearall(eosio::unpack_action_data<clear>());
                break;
            }
        default:
            break;
    }

} // extern "C"
}
