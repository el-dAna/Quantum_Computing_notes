
# leetcode 30/09/2023
import numpy as np
class Solution:
    def find132pattern(self, nums: List[int]) -> bool:
        if len(nums) < 3:
            return False

        numa = np.array(nums)
        print(numa)
        for i,num in enumerate(nums[:-2]):
            print("num", num)
            poss = (np.where(numa[i+1:] > num))[0] + i + 1
            print(poss, "index:", i)
            for p in poss:
                print("num2", numa[p])
                poss2 = np.where(numa[p] > numa[p: poss[-1]])[0] + i + p 
                print("poss2", poss2, "poss[-1]:",numa[p: poss[-1]])
                for p2 in poss2:
                    print("num3", numa[p2])
                    if numa[p2] > num:
                        return True
            