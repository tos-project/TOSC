pragma solidity ^0.4.24;
import "./TOSC.sol";
import "./library/SafeMath.sol";
import "./owners.sol";

contract functions is owners{
    using SafeMath for uint;
    TOSC data;

    constructor(address _TOSCaddress) public {
        require(_TOSCaddress != address(0));
        data = TOSC(_TOSCaddress);
    }
    
    
    function currentDataAddress() public view returns(address){
        return data;
    }
    
    
     function transfer(address _to, uint256 _value) public{
        data.sendTransfer(msg.sender, _to, _value);
    }
    
    function transfer_admin(address _from, address _to, uint256 _value) onlyOwner public{
        data.sendTransfer(_from, _to, _value);
    }

    function transferToKeeper(address _from, uint256 _value) onlyKeeperOwner public{
        
        data.sendTransfer(_from, keeperOwner, _value);
    }

    // 현재 사용안함
    // function transferToTestKeeper(address _from, uint256 _value) onlyTestKeeperOwner public{
    //     address keeperAddress = 0xf65eeD7320D941DA807998a65AFa28a7CA0845e5;
    //     data.sendTransfer(_from, keeperAddress, _value);
    // }
    

    /// @notice `freeze? Prevent | Allow` `target` from sending & receiving tokens
    /// @param target Address to be frozen
    /// @param freeze either to freeze it or not
    function freezeAddress(address target, bool freeze) onlyOwner public {
        data.freezeAddress(target, freeze);
    }
    
    function percentLock(address target,uint percentage)onlyOwner public{
        require(percentage > 0 && percentage <= 100);
        
        uint percent = data.getBalance(target).mul(percentage).mul(100).div(10000);
        uint avliable = data.getBalance(target).sub(percent);
        data.PercentLock(target, percentage ,avliable);
    }
    
    function removePercentLock(address target)onlyOwner public{
        require(data.getpercentLockedAccount(target) == true);
        data.removePercentLock(target);
    }
    
    function percentLockCheck(address target) view public returns(string, uint256) {
        if(data.getpercentLockedAccount(target) == false){
            return ("This address is not locked", data.getpercentLockAvailable(target));
        }else{
            return ("This address is locked ↓↓ Avliable value", data.getpercentLockAvailable(target));
        }
    }
    
    
     function burn(uint256 _value) public {
        require(data.getBalance(msg.sender) >= _value);   // Check if the sender has enough
        data.burn(msg.sender,_value);
    }
    
    function balanceOf(address addr) public view returns(uint256){
        return data.getBalance(addr);
    }
    
    function frozenAdress(address addr) public view returns(bool){
        return data.getfrozenAddress(addr);
    }
    
    
    
    
    function recliamOwnership() public onlyOwner {
        data.transferOwnership(owner);
    }
    
}
