//: Playground - noun: a place where people can play

import Cocoa

//var INF = Int.max
var INF = 1000000




typealias GraphM = [[Int]]

typealias GraphL = [[Int: Int]]



func printGraphL(g: GraphL) -> ()
{
    for (source, list) in g.enumerated() {
        print("\(source)-->", terminator:"\t")
        for (dest, weight) in Array(list).sorted(by: { $0.0 < $1.0 }) {
            print("(\(dest),\(weight)) \t", terminator:"")
        }
        print()
    }
    print()
}




func graphL2M (gl: GraphL) -> GraphM {
    let N = gl.count
    let nodes = 0...N-1
    var gm: GraphM = Array(repeating: Array(repeating: INF, count: N), count: N)

    for source in nodes {
        for (dest, weight) in gl[source] {
            gm[source][dest] = weight
        }
    }
    return gm
}


// To get a proper adj-list representation we omit the INF edges when converting
// from an adjacency matrix. These entries become nil in the dictionaries.

func graphM2L (g: GraphM) -> GraphL {
    var gl: GraphL = Array(repeating: [:], count: g.count)
    let nodes = 0...g.count-1
    
    for i in nodes {
        for j in nodes {
            if g[i][j] != INF {
                gl[i][j] = g[i][j]
            }
        }
    }
    return gl
}



struct Queue {
    var state : [Int]

    init () {
        state = []
    }
    
    func isEmpty () -> Bool {
        return state.isEmpty
    }
    
    mutating func enqueue (x: Int) -> () {
        state.append(x)
    }

    mutating func dequeue () -> Int {
        let r = state[0]
        state.remove(at: 0)
        return r
    }
}


enum Color {
    case White
    case Gray
    case Black
}



func bfs (g: GraphL, s: Int) -> ([Int], [Int])
{
    let N = g.count

    var parent : [Int] = Array(repeating: -1, count: N)
    var dist : [Int] = Array(repeating: NSIntegerMax, count: N)

    var color : [Color] = Array(repeating: Color.White, count: N)
    var q = Queue()
    var u : Int
    
    color[s] = Color.Gray
    dist[s] = 0
    q.enqueue(x: s)

    while !q.isEmpty() {
        u = q.dequeue()
        for (v,_) in g[u] {
            if color[v] == Color.White {
                color[v] = Color.Gray
                print(v, "Gray")
                dist[v] = dist[u] + 1
                parent[v] = u
                q.enqueue(x: v)
            }
        }
        color[u] = Color.Black
        print(u, "Black")
    }
    
    return (parent, dist)
}



func cdfs (g:GraphL) -> [Int]
{
    let N = g.count
    let nodes = 0...N-1
    
    var parent : [Int] = Array(repeating: -1, count: N)
    
    var color : [Color] = Array(repeating: Color.White, count: N)

    
    func dfs (g:GraphL, s:Int) -> ()
    {
        color[s] = Color.Gray
        print(s, "Gray")
        for (v,_) in g[s] {
            if color[v] == Color.White {
                parent[v] = s
                dfs (g: g, s: v)
            }
        }
        color[s] = Color.Black
        print(s, "Black")
    }
    
    for u in nodes {
        if color[u] == Color.White {
            dfs(g: g, s: u)
        }
    }
    return parent
}











// Standard Warshall algorithm is straightforward to write
func Warshall (g:GraphM) -> GraphM
{
    var distance: GraphM = g
    let nodes = 0...g.count-1
    
    for k in nodes {
        for i in nodes {
            for j in nodes {
                distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j])
            }
        }
    }
    return distance
}



// More interesting is Warshall on the adj. list / dictionaries representation
// This shows that it is pointless to use an actual matrix-based representation,
// since  traditional matrix algorithms can easily be coded for dict-based adj lists.

func Warshall(g:GraphL) -> GraphL
{
    var distance: GraphL = g
    var dikj: Int
    let nodes = 0...g.count-1
    
    for k in nodes {
        for i in nodes {
            for j in nodes {
                if distance[i][k] != nil && distance[k][j] != nil {
                    dikj = distance[i][k]! + distance[k][j]!
                    if distance[i][j] != nil {
                        distance[i][j] = min(distance[i][j]!, dikj)
                    }
                    else {
                        distance[i][j] = dikj
                    }
                }
                //  else there is nothing to do, regardless of whether distance[i]![j] is nil
            }
        }
    }
    return distance
}



var gm1 : GraphM = [
    [ INF,   1, INF,   2 ],
    [ INF, INF,   1,   2 ],
    [   1, INF, INF,   2 ],
    [   1,   1,   1, INF ],
]

var gm2 : GraphM = [
    [ INF,   1, INF, INF, INF, INF, INF, INF, INF ],
    [ INF, INF,   1, INF, INF, INF,   1, INF, INF ],
    [ INF, INF, INF, INF, INF, INF, INF,   1, INF ],
    [ INF, INF,   1, INF,   1, INF, INF,   1, INF ],
    [ INF, INF, INF, INF, INF, INF, INF, INF, INF ],
    [   1, INF, INF, INF,   1, INF, INF, INF,   1 ],
    [   1, INF, INF, INF, INF, INF, INF, INF, INF ],
    [ INF, INF, INF, INF, INF, INF,   1, INF,   1 ],
    [ INF, INF, INF, INF,   1, INF,   1, INF, INF ],
]



var gl1 = graphM2L(g: gm1)
var gl2 = graphM2L(g: gm2)

//printGraphL(g: gl1)

let (parent, dist) = bfs(g: gl2, s: 3)

print ("BF traversal tree:", parent)
print ("Distances:", dist)


//let parent = cdfs(g: gl2)

//print (parent)





//print (Warshall(g: gm1), "\n")
//
//printGraphL(g:Warshall(g: graphM2L(g: gm1)))




