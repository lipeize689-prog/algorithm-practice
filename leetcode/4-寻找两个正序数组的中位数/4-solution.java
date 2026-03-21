class Solution {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        ArrayList<Integer> newArray = new ArrayList<>();
        
        for(int num : nums1){
            newArray.add(num);
        }
        for(int num : nums2){
            newArray.add(num);
        }
        
        Collections.sort(newArray);
        
        if(newArray.size() % 2 != 0){
            return (double) (newArray.get(newArray.size() / 2));
        }

        return (double) (newArray.get((newArray.size() + 1) / 2) + newArray.get((newArray.size() - 1) / 2)) / 2;
    }
}