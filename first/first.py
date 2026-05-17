import ast


class PythonToJavaTranslator(ast.NodeVisitor):

    def __init__(self):
        self.java_code = []
        self.indent_level = 2
        self.variables = set()

    def indent(self):
        return " " * (self.indent_level * 4)

    def translate(self, code):

        tree = ast.parse(code)

        self.java_code.append("public class Main {")
        self.java_code.append("    public static void main(String[] args) {")

        self.visit(tree)

        self.java_code.append("    }")
        self.java_code.append("}")

        return "\n".join(self.java_code)


    def visit_Assign(self, node):

        target = node.targets[0].id
        value = self.visit(node.value)

        if target not in self.variables:
            self.variables.add(target)
            line = f"{self.indent()}int {target} = {value};"
        else:
            line = f"{self.indent()}{target} = {value};"

        self.java_code.append(line)

    def visit_Constant(self, node):
        return str(node.value)

    def visit_Name(self, node):
        return node.id

    def visit_BinOp(self, node):

        left = self.visit(node.left)
        right = self.visit(node.right)

        op = self.get_operator(node.op)

        return f"{left} {op} {right}"
    
    def visit_Call(self, node):

        if isinstance(node.func, ast.Name):

            if node.func.id == "print":

                arg = self.visit(node.args[0])

                line = (
                    f"{self.indent()}System.out.println({arg});"
                )

                self.java_code.append(line)


    def visit_Expr(self, node):
        self.visit(node.value)


    def visit_If(self, node):

        condition = self.visit(node.test)

        self.java_code.append(
            f"{self.indent()}if ({condition}) {{"
        )

        self.indent_level += 1

        for stmt in node.body:
            self.visit(stmt)

        self.indent_level -= 1

        self.java_code.append(
            f"{self.indent()}}}"
        )

    def visit_While(self, node):

        condition = self.visit(node.test)

        self.java_code.append(
            f"{self.indent()}while ({condition}) {{"
        )

        self.indent_level += 1

        for stmt in node.body:
            self.visit(stmt)

        self.indent_level -= 1

        self.java_code.append(
            f"{self.indent()}}}"
        )


    def visit_Compare(self, node):

        left = self.visit(node.left)
        right = self.visit(node.comparators[0])

        op = self.get_compare_operator(node.ops[0])

        return f"{left} {op} {right}"


    def get_operator(self, op):

        operators = {
            ast.Add: "+",
            ast.Sub: "-",
            ast.Mult: "*",
            ast.Div: "/",
            ast.Mod: "%"
        }

        return operators[type(op)]

    def get_compare_operator(self, op):

        operators = {
            ast.Lt: "<",
            ast.Gt: ">",
            ast.Eq: "==",
            ast.NotEq: "!=",
            ast.LtE: "<=",
            ast.GtE: ">="
        }

        return operators[type(op)]




python_code = """
x = 10
y = 20

if x < y:
    print(x + y)

while x < 15:
    print(x)
    x = x + 1
"""



translator = PythonToJavaTranslator()

java_code = translator.translate(python_code)



print("===== JAVA CODE =====")
print(java_code)