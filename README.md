bogon:outerNetDataService cl$ cleos create key
Private key: 5Jq9M7geANKBvPSQxtezen6GNq9Tud41fE5nbKmWHP8rCjz2Q8X
Public key: EOS8QpGAezXHLGpR9yanyNPPn2ttyJ6hZdeijqeryMKATZYt6zRD9
bogon:outerNetDataService cl$ cleos create key
Private key: 5JLejzjwsGVN8LqgLve4PjcSy2DbWtpNqA7LjdocEHF5hGs7m3N
Public key: EOS7d7bz8yVd1ntEmQtEe3UeaG4QY6Zc2cgBtoVRLaBY79D1rNEpu


cleos -u http://127.0.0.1:8889/ --wallet-url http://127.0.0.1:8890/ wallet import 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3
cleos -u http://127.0.0.1:8889/ --wallet-url http://127.0.0.1:8890/ wallet import 5Jq9M7geANKBvPSQxtezen6GNq9Tud41fE5nbKmWHP8rCjz2Q8X




cleos -u http://127.0.0.1:8889/ --wallet-url http://127.0.0.1:8890/ create account eosio outnetserver EOS8gb6EkQDry72Ugwwy6MUZCr7EQ4ytGAeRhu3knVsA3qSneWPEb EOS6BB3rfssiBdiBN2d14GQLswcM1KBmcKWEM8fiSmdLw6eKWP5et
cleos -u http://127.0.0.1:8889/ --wallet-url http://127.0.0.1:8890/ create account eosio ondsadmin EOS8gb6EkQDry72Ugwwy6MUZCr7EQ4ytGAeRhu3knVsA3qSneWPEb EOS6BB3rfssiBdiBN2d14GQLswcM1KBmcKWEM8fiSmdLw6eKWP5et


cleos  -u http://127.0.0.1:8889/ --wallet-url http://127.0.0.1:8890/  set contract outnetserver ./ outerNetDataService.wast outerNetDataService.abi -p outnetserver