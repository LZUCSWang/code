/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\OTHER\x.java
 * @Description: 
 */
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class Main {
public static void main(String[] args) {
Scanner scanner = new Scanner(System.in);
int t = scanner.nextInt();
int n = scanner.nextInt();
List<Pair<Integer, Integer>> ver = new ArrayList<>();
    for (int i = 1; i <= n; i++) {
        int x = scanner.nextInt();
        int y = scanner.nextInt();
        ver.add(new Pair<>(x, y));
    }

    Collections.sort(ver);

    int now = 1;
    int pos = 0;
    int ans = 0;

    while (pos < ver.size() && now <= t) {
        int mx = 0;

        while (pos < ver.size() && ver.get(pos).first <= now) {
            mx = Math.max(mx, ver.get(pos).second);
            pos++;
        }

        if (mx <= now - 1) {
            break;
        }

        now = mx + 1;
        ans++;
    }

    if (now > t) {
        System.out.println(ans);
    } else {
        System.out.println(-1);
    }
}}

static class Pair<T1, T2> implements Comparable<Pair<T1, T2>> {
    T1 first;
    T2 second;

    Pair(T1 first, T2 second) {
        this.first = first;
        this.second = second;
    }

    @Override
    public int compareTo(Pair<T1, T2> other) {
        if (first.equals(other.first)) {
            return ((Comparable<T2>) second).compareTo(other.second);
        } else {
            return ((Comparable<T1>) first).compareTo(other.first);
        }
    }
}
