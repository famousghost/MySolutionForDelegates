# Simple Delegate system

# Usage
## Delcaration
### Delegate<retType(arguments...)> delegateName
		
## Register Methods
### delegateName.REGISTER_METHOD(this, &A::Method) -> registering any method
### delegateName.REGISTER_FUNC(func) -> registering any func
	
## Unregister Methods
### delegateName.REGISTER_METHOD(this, &A::Method) -> registering any method
### delegateName.REGISTER_FUNC(func) -> registering any func
## Invoke Methods
### delegateName.Invoke({arguments...})
### auto values = delegateName.InvokeRet({arguments...})
		
@copyright Marcin Czekaj
