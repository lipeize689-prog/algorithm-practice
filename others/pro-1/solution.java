import java.io.*;
import java.util.*;

public class Main{
    static Map<Integer, Node> map = new HashMap<>();
    static Map<Integer, LinkedHashSet<Node>> freqMap = new HashMap<>();
    static Queue<TimeNode> q = new LinkedList<>(); 
    static int N, M, T;
    static int minFreq;
    static int currentTime = 0;

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        String[] first = br.readLine().split(" ");
        N = Integer.parseInt(first[0]);M = Integer.parseInt(first[1]);T = Integer.parseInt(first[2]);
        while(M-- > 0){
            String[] others = br.readLine().split(" ");
            currentTime++;
            expire();
            if(others.length == 2){
                int key = Integer.parseInt(others[1]);
                if(map.containsKey(key)){
                    bw.write(map.get(key).value + "\n");
                    get(key);
                }else{
                    bw.write("-1\n");
                }
            }
            else{
                int key = Integer.parseInt(others[1]);
                int value = Integer.parseInt(others[2]);
                put(key, value);
            }

        }
        List<Node> list = new ArrayList<>(map.values());
        list.sort(Comparator.comparingInt(a -> a.time));
        if(list.isEmpty()) bw.write("empty");
        else{
            for(Node node : list){
                bw.write(node.value + " ");
            }
        }
        bw.flush();
        br.close();
        bw.close();
    }

    public static void expire(){
        while(!q.isEmpty()){
            TimeNode t = q.peek();
            if(currentTime - t.time <= T) break;
            q.poll();
            Node node = t.node;
            if(node.time != t.time) continue;   // 懒删除核心
            LinkedHashSet<Node> set = freqMap.get(node.freq);
            if(set != null){
                set.remove(node);
                if(set.isEmpty()){
                    freqMap.remove(node.freq);
                    if(node.freq == minFreq){
                        minFreq++;
                    }
                }
            }
            map.remove(node.key);
        }
    }

    public static void get(int key){
        if(!map.containsKey(key)) return;
        Node node = map.get(key);
        LinkedHashSet<Node> set = freqMap.get(node.freq);
        set.remove(node);
        if(set.isEmpty()){
            freqMap.remove(node.freq);
            if(node.freq == minFreq){
                minFreq++;
            }
        }
        node.freq++;
        freqMap.computeIfAbsent(node.freq, k -> new LinkedHashSet<>());
        freqMap.get(node.freq).add(node);
        node.time = currentTime;
        q.offer(new TimeNode(currentTime, node));
    }

    public static void put(int key, int value){
        if(N == 0) return;
        if(map.containsKey(key)){
            map.get(key).value = value;
            get(key);
            return;
        }
        if(map.size() == N){
            LinkedHashSet<Node> set = freqMap.get(minFreq);
            Node old = set.iterator().next();
            set.remove(old);
            if(set.isEmpty()){
                freqMap.remove(old.freq);
            }
            map.remove(old.key);
        }
        Node node = new Node(key, value);
        node.time = currentTime;
        map.put(key, node);
        freqMap.computeIfAbsent(1, k -> new LinkedHashSet<>());
        freqMap.get(1).add(node);
        minFreq = 1;
        q.offer(new TimeNode(currentTime, node));
    }

    static class Node{
        int key, value;
        int time, freq;
        public Node(int key, int value){
            this.key = key;
            this.value = value;
            this.freq = 1;
        }

        @Override
        public int hashCode(){
            return Objects.hash(key);
        }

        @Override
        public boolean equals(Object o){
            if(this == o) return true;
            if(!(o instanceof Node)) return false;
            return ((Node) o).key == this.key;
        }
    }

    static class TimeNode{
        int time;
        Node node;
        public TimeNode(int time, Node node){
            this.time = time;
            this.node = node;
        }
    }
}