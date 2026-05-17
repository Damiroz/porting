import ast


class PythonToJavaTranslator(ast.NodeVisitor):

    def __init__(self):
        self.java_code = []
        self.indent_level = 1
        self.variables = set()

    def indent(self):
        return "    " * self.indent_level

    def translate(self, code):

        tree = ast.parse(code)

        self.java_code.append("public class Main {")

        self.visit(tree)

        self.java_code.append("}")

        return "\n".join(self.java_code)

    def visit_FunctionDef(self, node):

        args = []

        for arg in node.args.args:
            args.append(f"int {arg.arg}")

        args_str = ", ".join(args)

        self.java_code.append(
            f"{self.indent()}public static int {node.name}({args_str}) {{"
        )

        self.indent_level += 1

        for stmt in node.body:
            self.visit(stmt)

        self.indent_level -= 1

        self.java_code.append(f"{self.indent()}}}")

    def visit_Return(self, node):

        value = self.visit(node.value)

        self.java_code.append(
            f"{self.indent()}return {value};"
        )

    def visit_Assign(self, node):

        target = node.targets[0].id
        value = self.visit(node.value)

        if target not in self.variables:
            self.variables.add(target)

            line = f"{self.indent()}int {target} = {value};"

        else:
            line = f"{self.indent()}{target} = {value};"

        self.java_code.append(line)

    def visit_Name(self, node):
        return node.id

    def visit_Constant(self, node):
        return str(node.value)

    def visit_BinOp(self, node):

        left = self.visit(node.left)
        right = self.visit(node.right)

        if isinstance(node.op, ast.Pow):
            return f"((int)Math.pow({left}, {right}))"

        op = self.get_operator(node.op)

        return f"{left} {op} {right}"

    def visit_Call(self, node):

        if isinstance(node.func, ast.Name):

            func_name = node.func.id

            args = []

            for arg in node.args:
                args.append(self.visit(arg))

            args_str = ", ".join(args)

            return f"{func_name}({args_str})"

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

        if node.orelse:

            self.java_code.append(
                f"{self.indent()}else {{"
            )

            self.indent_level += 1

            for stmt in node.orelse:
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
def factorial(n):

    if n == 0:
        return 1
    else:
        return n * factorial(n - 1)


def fibonacci(n):

    if n <= 1:
        return n
    else:
        return fibonacci(n - 1) + fibonacci(n - 2)


def power(a, b):

    return a ** b
"""

translator = PythonToJavaTranslator()

java_code = translator.translate(python_code)

print(java_code)

with open("Main.java", "w") as f:
    f.write(java_code)