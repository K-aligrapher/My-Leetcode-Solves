class Solution:
    def minInsertions(self, s: str) -> int:
        insertions = 0
        needed_right = 0
        
        for c in s:
            if c == '(':
                if needed_right % 2 == 1:
                    insertions += 1
                    needed_right -= 1
                needed_right += 2
            else: 
                needed_right -= 1
                if needed_right < 0:
                    insertions += 1
                    needed_right += 2
                    
        return insertions + needed_right
