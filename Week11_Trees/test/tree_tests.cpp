#include <gtest/gtest.h>
#include "../include/BinaryTree.hpp"
#include "../include/NAryTree.hpp"
#include "../include/ArrayBinaryTree.hpp"

class BinaryTreeTest : public ::testing::Test {
protected:
    BinaryTree<int> tree;
    
    void SetUp() override {
        // Test ağacını oluştur
        tree.insert(1);
        tree.insert(2);
        tree.insert(3);
        tree.insert(4);
        tree.insert(5);
    }
};

TEST_F(BinaryTreeTest, InitialState) {
    BinaryTree<int> emptyTree;
    EXPECT_TRUE(emptyTree.isEmpty());
    EXPECT_EQ(emptyTree.getHeight(), -1);
    EXPECT_EQ(emptyTree.getNodeCount(), 0);
    EXPECT_EQ(emptyTree.getLeafCount(), 0);
}

TEST_F(BinaryTreeTest, BasicProperties) {
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(tree.getHeight(), 2);
    EXPECT_EQ(tree.getNodeCount(), 5);
    EXPECT_EQ(tree.getLeafCount(), 3);
}

TEST_F(BinaryTreeTest, Traversals) {
    std::vector<int> expectedPreorder = {1, 2, 4, 5, 3};
    std::vector<int> expectedInorder = {4, 2, 5, 1, 3};
    std::vector<int> expectedPostorder = {4, 5, 2, 3, 1};
    std::vector<int> expectedLevelorder = {1, 2, 3, 4, 5};
    
    EXPECT_EQ(tree.preorderTraversal(), expectedPreorder);
    EXPECT_EQ(tree.inorderTraversal(), expectedInorder);
    EXPECT_EQ(tree.postorderTraversal(), expectedPostorder);
    EXPECT_EQ(tree.levelorderTraversal(), expectedLevelorder);
}

TEST_F(BinaryTreeTest, IterativeTraversals) {
    std::vector<int> expectedPreorder = {1, 2, 4, 5, 3};
    std::vector<int> expectedInorder = {4, 2, 5, 1, 3};
    
    EXPECT_EQ(tree.iterativePreorder(), expectedPreorder);
    EXPECT_EQ(tree.iterativeInorder(), expectedInorder);
}

TEST_F(BinaryTreeTest, CopyConstructor) {
    BinaryTree<int> treeCopy(tree);
    
    EXPECT_EQ(treeCopy.getHeight(), tree.getHeight());
    EXPECT_EQ(treeCopy.getNodeCount(), tree.getNodeCount());
    EXPECT_EQ(treeCopy.preorderTraversal(), tree.preorderTraversal());
}

TEST_F(BinaryTreeTest, AssignmentOperator) {
    BinaryTree<int> treeCopy;
    treeCopy = tree;
    
    EXPECT_EQ(treeCopy.getHeight(), tree.getHeight());
    EXPECT_EQ(treeCopy.getNodeCount(), tree.getNodeCount());
    EXPECT_EQ(treeCopy.preorderTraversal(), tree.preorderTraversal());
}

TEST_F(BinaryTreeTest, CreateFromTraversals) {
    BinaryTree<int> newTree;
    std::vector<int> preorder = {1, 2, 4, 5, 3};
    std::vector<int> inorder = {4, 2, 5, 1, 3};
    std::vector<int> postorder = {4, 5, 2, 3, 1};
    
    newTree.createFromPreorderInorder(preorder, inorder);
    EXPECT_EQ(newTree.preorderTraversal(), preorder);
    EXPECT_EQ(newTree.inorderTraversal(), inorder);
    
    newTree.createFromPostorderInorder(postorder, inorder);
    EXPECT_EQ(newTree.postorderTraversal(), postorder);
    EXPECT_EQ(newTree.inorderTraversal(), inorder);
}

class NAryTreeTest : public ::testing::Test {
protected:
    NAryTree<int> tree;
    
    void SetUp() override {
        tree.insert(0, 1);  // root
        tree.insert(1, 2);  // 1'in çocuğu
        tree.insert(1, 3);  // 1'in çocuğu
        tree.insert(2, 4);  // 2'nin çocuğu
    }
};

TEST_F(NAryTreeTest, BasicOperations) {
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(tree.getHeight(), 2);
    EXPECT_EQ(tree.getNodeCount(), 4);
    EXPECT_EQ(tree.getLeafCount(), 2);
    EXPECT_EQ(tree.getMaxDegree(), 2);
}

TEST_F(NAryTreeTest, Traversals) {
    std::vector<int> expectedLevelOrder = {1, 2, 3, 4};
    std::vector<int> expectedPreorder = {1, 2, 4, 3};
    std::vector<int> expectedPostorder = {4, 2, 3, 1};
    
    EXPECT_EQ(tree.levelOrderTraversal(), expectedLevelOrder);
    EXPECT_EQ(tree.preorderTraversal(), expectedPreorder);
    EXPECT_EQ(tree.postorderTraversal(), expectedPostorder);
}

class ArrayBinaryTreeTest : public ::testing::Test {
protected:
    ArrayBinaryTree<int>* tree;
    
    void SetUp() override {
        tree = new ArrayBinaryTree<int>(-1);  // -1 as null value
        tree->insert(1);
        tree->insert(2);
        tree->insert(3);
        tree->insert(4);
        tree->insert(5);
    }
    
    void TearDown() override {
        delete tree;
    }
};

TEST_F(ArrayBinaryTreeTest, BasicOperations) {
    EXPECT_FALSE(tree->isEmpty());
    EXPECT_EQ(tree->getSize(), 5);
    EXPECT_EQ(tree->getHeight(), 2);
    EXPECT_EQ(tree->getLeafCount(), 3);
}

TEST_F(ArrayBinaryTreeTest, Traversals) {
    std::vector<int> expectedPreorder = {1, 2, 4, 5, 3};
    std::vector<int> expectedInorder = {4, 2, 5, 1, 3};
    std::vector<int> expectedPostorder = {4, 5, 2, 3, 1};
    std::vector<int> expectedLevelOrder = {1, 2, 3, 4, 5};
    
    EXPECT_EQ(tree->preorderTraversal(), expectedPreorder);
    EXPECT_EQ(tree->inorderTraversal(), expectedInorder);
    EXPECT_EQ(tree->postorderTraversal(), expectedPostorder);
    EXPECT_EQ(tree->levelOrderTraversal(), expectedLevelOrder);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 