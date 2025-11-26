fun main() {
    val reader = FastScanner()
    val out = PrintWriter(System.out)
    val aStr = reader.next()
    val a = aStr.toBigInteger()
    val c = reader.next().toBigDecimal()
    out.flush()
}

// Efficient Input Reader
class FastScanner {
    var tokenizer = StringTokenizer("")
    var reader = BufferedReader(InputStreamReader(System.`in`))
    fun next(): String {
        while (!tokenizer.hasMoreTokens()) {
            val line = reader.readLine() ?: return ""
            tokenizer = StringTokenizer(line)
        }
        return tokenizer.nextToken()
    }
    fun nextInt(): Int = next().toInt()
    fun nextLong(): Long = next().toLong()
    fun nextDouble(): Double = next().toDouble()
}
