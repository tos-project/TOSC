pragma solidity ^0.4.24;
contract owners {
    address public owner;
    address public keeperOwner;
    address public testKeeperOwner;
    constructor() public {
        owner = msg.sender;
        keeperOwner = msg.sender;
        // testKeeperOwner = 0xf65eeD7320D941DA807998a65AFa28a7CA0845e5;
    }

    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }

    modifier onlyKeeperOwner {
        require(msg.sender == keeperOwner);
        _;
    }
    
    // modifier onlyTestKeeperOwner {
    //     require(msg.sender == testKeeperOwner);
    //     _;
    // }

    function transferOwnership(address newOwner) onlyOwner public {
        require(newOwner != owner);
        owner = newOwner;
    }
    
    function transferKeeperOwnership(address newOwner) onlyOwner public {
        require(newOwner != keeperOwner);
        keeperOwner = newOwner;
    }
    
    // function transferTestKeeperOwnership(address newOwner) onlyOwner public {
    //     require(newOwner != testKeeperOwner);
    //     testKeeperOwner = newOwner;
    // }
}