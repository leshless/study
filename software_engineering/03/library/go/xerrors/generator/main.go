package main

import (
	_ "embed"
	"fmt"
	"go/ast"
	"go/parser"
	"go/token"
	"os"
	"strings"
	"text/template"

	"github.com/leshless/golibrary/stringcase"
)

//go:embed error.go.tpl
var errorFileTpl string
var errorFileTemplate = template.Must(template.New("error").Parse(errorFileTpl))

const (
	libraryPath = "swe3/library/go/xerrors"
)

type errorFileCriteria struct {
	FileName     string
	PackageName  string
	ErrorName    string
	ErrorCode    string
	ErrorText    string
	ErrorMessage string
	LibraryPath  string
}

func main() {
	sourceFileName := os.Getenv("GOFILE")

	sourceFile, err := parser.ParseFile(token.NewFileSet(), sourceFileName, nil, parser.ParseComments)
	if err != nil {
		os.Exit(1)
	}

	stack := make([]ast.Node, 0)
	criterias := make([]errorFileCriteria, 0)

	ast.Inspect(sourceFile, func(node ast.Node) bool {
		var next bool
		switch node := node.(type) {
		case *ast.File:
			next = true
		case *ast.GenDecl:
			next = true
		case *ast.TypeSpec:
			comment, ok := stack[len(stack)-1].(*ast.CommentGroup)
			if !ok {
				os.Exit(1)
			}

			specs := strings.Split(comment.Text(), "\n")
			if len(specs) != 4 {
				os.Exit(1)
			}

			criterias = append(criterias, errorFileCriteria{
				FileName:     sourceFileName,
				PackageName:  sourceFile.Name.Name,
				ErrorName:    node.Name.Name,
				ErrorCode:    specs[0],
				ErrorText:    specs[1],
				ErrorMessage: specs[2],
				LibraryPath:  libraryPath,
			})

			next = false
		}

		if node == nil {
			stack = stack[:len(stack)-1]
		} else {
			stack = append(stack, node)
		}

		return next
	})

	for _, criteria := range criterias {
		err = createErrorFileFromCriteria(criteria)
		if err != nil {
			os.Exit(1)
		}
	}
}

func createErrorFileFromCriteria(criteria errorFileCriteria) error {
	fileName := fmt.Sprintf("%s.gen.go", stringcase.LowerSnake(strings.TrimSuffix(criteria.ErrorName, "Error")))

	file, err := os.Create(fileName)
	if err != nil {
		return fmt.Errorf("creating file: %w", err)
	}
	defer func() { _ = file.Close() }()

	err = errorFileTemplate.Execute(file, criteria)
	if err != nil {
		return fmt.Errorf("executing template: %w", err)
	}

	return nil
}
