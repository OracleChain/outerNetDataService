/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eosiolib/eosio.hpp>
#include <eosiolib/db.h>
#include <eosiolib/asset.hpp>
#include<eosiolib/serialize.hpp>

#define POST_METHOD 0
#define GET_METHOD 1

#define STATUS_NOT_DEALING 0
#define STATUS_DEALED 1
#define URL_CANNOT_ACCESS 2

#define LIMITED_ONLY_ADMIN_CAN_DO "6000000 PERMISSION LIMITED_ONLY_ADMIN_CAN_DO" //参数错误
#define ID_NOT_EXIST "6000001 ID_NOT_EXIST" //参数错误
/*
@abi action addwebreq
*/
struct webrequest{
    account_name  from;//must be one contract
    std::string url;
    std::string postdata;//post method parameter
    uint32_t method;//post or get
    uint64_t requesttimestamp;//web grab data time
    std::string memo;

    account_name primary_key()const { return from;}

    EOSLIB_SERIALIZE(webrequest, (from)(url)(postdata)(method)(requesttimestamp)(memo))
};


/*
@abi action addwebres
*/
struct webresult{
    uint64_t id;
    std::string webdata;
    uint32_t status;
    std::string errmsg;
    EOSLIB_SERIALIZE(webresult, (id)(webdata)(status)(errmsg))
};

/*
@abi action clearall
*/
struct clear{
    std::string debug;
    EOSLIB_SERIALIZE(clear, (debug))
};

/*
@abi table web
*/
struct web{
    uint64_t id;
    account_name  from;//must be one contract
    std::string url;
    std::string postdata;//post method parameter
    uint32_t method;//post or get
    uint64_t requesttimestamp;//web grab data time
    uint32_t status;
    std::string memo;



    uint64_t primary_key()const { return id;}
    account_name get_secondary()const { return from; }

    void copyFrom(const webrequest & p){
        this->from = p.from;
        this->url = p.url;
        this->postdata = p.postdata;
        this->method = p.method;
        this->requesttimestamp = p.requesttimestamp;
        this->status = STATUS_NOT_DEALING;
        this->memo = p.memo;
    }

    EOSLIB_SERIALIZE(web, (id)(from)(url)(postdata)(method)(requesttimestamp)(status)(memo)(webdata)(errmsg)(releasetime))
};

/*
@abi table webres
*/
struct webres{
    uint64_t id;
    std::string webdata;
    std::string errmsg;
    uint64_t releasetime;

    EOSLIB_SERIALIZE(webres, (id)(webdata)(errmsg)(releasetime))
};

class OutNetDataSer{
public:
    void storeWebRequest(const webrequest & parrequestweb);

    void storeWebResult(const webresult & parwebresult);

    void clearall(const clear & c);
    const uint64_t admin = N(ondsadmin);

    const uint64_t contractCode = N(outnetserver);
};



typedef eosio::multi_index<N(web), web,
   eosio::indexed_by< N(bysecondary), eosio::const_mem_fun<web,  account_name, &web::get_secondary> >> ReqWebTable;

typedef eosio::multi_index<N(webres), webres> MultiIndexWebRes;
