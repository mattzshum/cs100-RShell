#include "And.h"
#include "Or.h"
#include "Semi.h"
#include "Command.h"

#include "gtest/gtest.h"

//create test for connector classes
TEST(Construct,Command){
   Command* test = new Command("ls");
   EXPECT_EQ(1,test->execute());
} 

TEST(Construct, Or){
   Command* left = new Command("ls");
   Command* right = new Command("echo hello");
   Or* test = new Or(left,right);
   EXPECT_EQ(1,test->execute());
}

TEST(Construct,And){
   Command* left = new Command("ls");
   Command* right = new Command("echo hello");
   And* test = new And(left,right);
   EXPECT_EQ(1,test->execute());
}


//create test for commands
//

