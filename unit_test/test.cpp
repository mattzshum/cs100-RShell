#include "And.h"
#include "Or.h"
#include "Semi.h"
#include "Command.h"
#include "Base.h"

#include "gtest/gtest.h"

//create test for connector classes
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

TEST(Construct, Semi){
   Command* left = new Command("ls");
   Command* right = new Command("echo hello");
   Or* test = new Semi(left,right);
   EXPECT_EQ(1,test->execute());
}

TEST(Construct, Or2){
   Command* left = new Command("ls -a");
   Command* right = new Command("echo hello");
   Or* test = new Or(left,right);
   EXPECT_EQ(1,test->execute());
}

TEST(Construct,And2){
   Command* left = new Command("ls - a");
   Command* right = new Command("echo hello");
   And* test = new And(left,right);
   EXPECT_EQ(1,test->execute());
}

TEST(Construct, Semi2){
   Command* left = new Command("ls -a");
   Command* right = new Command("echo hello");
   Or* test = new Semi(left,right);
   EXPECT_EQ(1,test->execute());
}

TEST(Construct, Or3){
   Command* left = new Command("mkdir test");
   Command* right = new Command("echo hello");
   Or* test = new Or(left,right);
   EXPECT_EQ(1,test->execute());
}

TEST(Construct,And3){
   Command* left = new Command("mkdir test");
   Command* right = new Command("echo hello");
   And* test = new And(left,right);
   EXPECT_EQ(1,test->execute());
}

TEST(Construct, Semi3){
   Command* left = new Command("mkdir test");
   Command* right = new Command("echo hello");
   Or* test = new Semi(left,right);
   EXPECT_EQ(1,test->execute());
}

TEST(Construct, Or4){
   Command* left = new Command("ls -a");
   Command* right = new Command("ls");
   Or* test = new Or(left,right);
   EXPECT_EQ(1,test->execute());
}

TEST(Construct,And4){
   Command* left = new Command("ls - a");
   Command* right = new Command("echo ls");
   And* test = new And(left,right);
   EXPECT_EQ(1,test->execute());
}

TEST(Construct, Semi4){
   Command* left = new Command("ls -a");
   Command* right = new Command("echo mkdir");
   Or* test = new Semi(left,right);
   EXPECT_EQ(1,test->execute());
}

TEST(Construct, Or5){
   Command* left = new Command("mkdir five");
   Command* right = new Command("echo hi");
   Or* test = new Or(left,right);
   EXPECT_EQ(1,test->execute());
}

TEST(Construct,And5){
   Command* left = new Command("echo hi");
   Command* right = new Command("echo hello");
   And* test = new And(left,right);
   EXPECT_EQ(1,test->execute());
}

TEST(Construct, Semi5){
   Command* left = new Command("echo hi");
   Command* right = new Command("ls");
   Or* test = new Semi(left,right);
   EXPECT_EQ(1,test->execute());
}

//create test for commands
TEST(Command, ls){
   Command* test = new Command("ls");
   EXPECT_EQ(1,test->execute());
} 

TEST(Command, echo){
   Command* test = new Command("echo");
   EXPECT_EQ(1,test->execute());
} 

TEST(Command, mkdir){
   Command* test = new Command("mkdir");
   EXPECT_EQ(1,test->execute());
} 

TEST(Command, ls -a){
   Command* test = new Command("ls -a");
   EXPECT_EQ(1,test->execute());
} 

TEST(Command, ps){
   Command* test = new Command("ps");
   EXPECT_EQ(1,test->execute());
} 
