import Foundation
func solution(_ files:[String]) -> [String] {
    
    var tuple = [(head: String, number: String, tail: String, idx: Int)]()
    var numbers = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"]
    
    for idx in 0..<files.count{
        
        let head = files[idx].prefix{ !$0.isNumber }
        var number = ""
        for char in Array(files[idx])[(head.count)...]{
            if number.count < 5 && char.isNumber{
                number += String(char)
            }else{
                break
            }
        }
        let tail = files[idx].suffix(files[idx].count - (number.count + head.count))
        
        tuple.append((head: String(head), number: number, tail: String(tail), idx: idx))
    }
    
    tuple = tuple.sorted{
        let head1 = $0.head.lowercased()
        let head2 = $1.head.lowercased()
        
        let num1 = Int($0.number)!
        let num2 = Int($1.number)!
        
        if head1 == head2{
            if num1 == num2{
                return $0.idx < $1.idx
            }
            return num1 < num2
        }
        return head1 < head2
    }
    var result = [String]()
    for tuple in tuple {
        result.append("\(tuple.head)\(tuple.number)\(tuple.tail)")
    }
    
    return result
}