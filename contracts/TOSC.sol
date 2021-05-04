pragma solidity ^0.4.24;
import "./library/owned.sol";
import "./library/SafeMath.sol";
import "./interface/TokenERC20.sol";

contract TOSC is owned, TokenERC20 {
    using SafeMath for uint;
    mapping (address => bool) public frozenAddress;
    mapping (address => bool) percentLockedAddress;
    mapping (address => uint256) percentLockAvailable;

    /* This generates a public event on the blockchain that will notify clients */
    event FrozenFunds(address target, bool frozen);
    event PercentLocked(address target, uint percentage, uint256 availableValue);
    event PercentLockRemoved(address target);
    

    /* Initializes contract with initial supply tokens to the creator of the contract */
    constructor (
        uint256 initialSupply,
        string tokenName,
        string tokenSymbol
    ) TokenERC20(initialSupply, tokenName, tokenSymbol) public {}
    

   /* Internal transfer, only can be called by this contract */
    function _transfer(address _from, address _to, uint _value) internal {
        require (_to != 0x0);                               // Prevent transfer to 0x0 address. Use burn() instead
        require (balanceOf[_from] >= _value);               // Check if the sender has enough
        require (balanceOf[_to].add(_value) >= balanceOf[_to]); // Check for overflows
        require(!frozenAddress[_from]);                     // Check if sender is frozen
        require(!frozenAddress[_to]);                       // Check if recipient is frozen
        if(percentLockedAddress[_from] == true){
            require(_value <= percentLockAvailable[_from]);
            percentLockAvailable[_from] = percentLockAvailable[_from].sub(_value);
        }
        uint previousBalances = balanceOf[_from].add(balanceOf[_to]);
        balanceOf[_from] = balanceOf[_from].sub(_value);                         // Subtract from the sender
        balanceOf[_to] = balanceOf[_to].add(_value);                           // Add the same to the recipient
        assert(balanceOf[_from].add(balanceOf[_to]) == previousBalances);
        emit Transfer(_from, _to, _value);
    }

    /// @notice `freeze? Prevent | Allow` `target` from sending & receiving tokens
    /// @param target Address to be frozen
    /// @param freeze either to freeze it or not
    function freezeAddress(address target, bool freeze) onlyOwner public {
        frozenAddress[target] = freeze;
        emit FrozenFunds(target, freeze);
    }
    
    
    function PercentLock(address target,uint percentage, uint256 available) onlyOwner public{
    
        percentLockedAddress[target] = true;
        percentLockAvailable[target] = available;
  
        emit PercentLocked(target, percentage, available);
    }
    
    function removePercentLock(address target)onlyOwner public{
        percentLockedAddress[target] = false;
        percentLockAvailable[target] = 0;
        emit PercentLockRemoved(target);
    }
    
    
    
    function sendTransfer(address _from, address _to, uint256 _value)onlyOwner external{
        _transfer(_from, _to, _value);
    }
  
    
    

    function getBalance(address addr) external view onlyOwner returns(uint256){
        return balanceOf[addr];
    }
    
    function getfrozenAddress(address addr) onlyOwner external view returns(bool){
        return frozenAddress[addr];
    }
    
    function getpercentLockedAccount(address addr) onlyOwner external view returns(bool){
        return percentLockedAddress[addr];
    }
    
    
    function getpercentLockAvailable(address addr) onlyOwner external view returns(uint256){
        return percentLockAvailable[addr];
    }

}




