[a,b]=list(map(lambda s:int(s),input().split(' ')))

modd=10**9+7
b%=(modd-1)
def mypower(base, exp):
    if exp==1:
        return base
    if exp==0:
        return 1
    copy=base
    currentpower=1
    while True:
        currentpower*=2
        copy*=copy
        copy%=modd
        if currentpower*2>exp:
            break
    return (copy*mypower(base,exp-currentpower))%modd
print(mypower(a,b))